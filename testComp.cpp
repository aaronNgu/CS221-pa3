#define CATCH_CONFIG_MAIN
#include "cs221util/catch.hpp"
#include <vector>
#include <sys/stat.h>
#include <iostream>
#include "cs221util/PNG.h"
#include "cs221util/HSLAPixel.h"
#include "stats.h"
#include "twoDtree.h"

using namespace std;
using namespace cs221util;

TEST_CASE("stats::basic rectArea","[weight=1][part=stats]"){

    PNG data; data.resize(2,2);
    stats s(data);
    pair<int,int> ul(0,0);
    pair<int,int> lr(1,1);
    long result = s.rectArea(ul,lr);

    REQUIRE(result == 4);

}

TEST_CASE("stats::basic getAvg","[weight=1][part=stats]"){
    PNG data; data.resize(2,2);
    for (int i = 0; i < 2; i ++){
        for (int j = 0; j < 2; j++){
            HSLAPixel * p = data.getPixel(i,j);
            p->h = 135*j + i * 90;
            p->s = 1.0;
            p->l = 0.5;
            p->a = 1.0;
        }
    }
    stats s(data);
    pair<int,int> ul(0,0);
    pair<int,int> lr(1,1);
    HSLAPixel result = s.getAvg(ul,lr);
    HSLAPixel expected(112.5,1.0, 0.5);

    REQUIRE(result == expected);
}

TEST_CASE("stats::basic entropy","[weight=1][part=stats]"){
    PNG data; data.resize(2,2);
    for (int i = 0; i < 2; i ++){
        for (int j = 0; j < 2; j++){
            HSLAPixel * p = data.getPixel(i,j);
            p->h = 135*j + i * 90;
            p->s = 1.0;
            p->l = 0.5;
            p->a = 1.0;
        }
    }
    stats s(data);
//    printf("seg fault entropy test 1\n");
    pair<int,int> ul(0,0);
//        printf("seg fault entropy test 2\n");
    pair<int,int> lr(1,1);
//        printf("seg fault entropy test 3\n");

    long result = s.entropy(ul,lr);
//        printf("seg fault entropy test 4\n");

    REQUIRE(result == 2);
}

TEST_CASE("twoDtree::basic ctor render","[weight=1][part=twoDtree]"){
      printf("seg fault 2dtree 1\n");
    PNG img;
    printf("seg fault 2dtree 2\n");
    img.readFromFile("images/ada.png");
    printf("seg fault 2dtree 3\n");

    twoDtree t1(img);
    printf("seg fault 2dtree 4\n");

    PNG out = t1.render();
    printf("seg fault 2dtree 5\n");

    REQUIRE(out==img);
}
TEST_CASE("twoDtree::basic copy","[weight=1][part=twoDtree]"){
    PNG img;
    img.readFromFile("images/ada.png");

    twoDtree t1(img);
    twoDtree t1copy(t1);

    PNG out = t1copy.render();

    REQUIRE(out==img);
}

TEST_CASE("twoDtree::basic prune","[weight=1][part=twoDtree]"){
    PNG img;
    img.readFromFile("images/color.png");

    twoDtree t1(img);

    PNG prePrune = t1.render();

    t1.prune(.05);
    PNG result = t1.render();
    PNG expected; expected.readFromFile("images/given-color.05.png");

    REQUIRE(expected==result);
}
