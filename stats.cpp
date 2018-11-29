
#include "stats.h"

stats::stats(PNG & im){

/* your code here! */
  //sumLum, sumSat, sumHueX, sumHueY
//cout<< "start stats 1"<< endl;
  HSLAPixel* currPixel;
//  cout<< "stats 2"<< endl;
  sumSat.resize(im.width(), vector<double>(im.height(), 0));
  sumLum.resize(im.width(), vector<double>(im.height(), 0));
  sumHueX.resize(im.width(), vector<double>(im.height(), 0));
  sumHueY.resize(im.width(), vector<double>(im.height(), 0));
  hist.resize(im.width(), vector<vector<int>>(im.height(), vector<int>(36,0)));

  for(int i = 0; i < (int)im.height(); i++){
//    cout<< "stats 3"<< endl;
    for(int j = 0; j < (int)im.width(); j++){
//      cout<< "stats 4"<< endl;
      currPixel = im.getPixel(j,i);
//      cout<< "stats 5"<< endl;
      if(i == 0 && j == 0){
//        cout<< "stats 6"<< endl;
        // starting pixel
        sumSat[j][i] = currPixel->s;
        sumLum[j][i] = currPixel->l;
        sumHueX[j][i] = cos((M_PI * currPixel->h)/180);
        sumHueY[j][i] = sin((M_PI * currPixel->h)/180);
        hist[j][i][floor(currPixel->h/10)]++;
//        printf("hist[%d][%d][%d] is %d \n", j,i,(int)floor(currPixel->h/10), hist[j][i][floor(currPixel->h/10)]);
      }else if(j == 0){
//        cout<< "stats 7"<< endl;
        // left bottom pixel
        sumSat[j][i] = sumSat[j][i-1] + currPixel->s;
        sumLum[j][i] = sumLum[j][i-1] + currPixel->l;
        sumHueX[j][i] = sumHueX[j][i-1] + cos((M_PI * currPixel->h)/180);
        sumHueY[j][i] = sumHueY[j][i-1] + sin((M_PI * currPixel->h)/180);
        createHistogram(j,i);
        hist[j][i][floor(currPixel->h/10)]++;
//        printf("hist[%d][%d][%d] is %d \n",j,i, (int)floor(currPixel->h/10), hist[j][i][floor(currPixel->h/10)]);
      }else if(i == 0){
//        cout<< "stats 8"<< endl;
        // right top pixel
        sumSat[j][i] = sumSat[j-1][i] + currPixel->s;
        sumLum[j][i] = sumLum[j-1][i] + currPixel->l;
        sumHueX[j][i] = sumHueX[j-1][i] + cos((M_PI * currPixel->h)/180);
        sumHueY[j][i] = sumHueY[j-1][i] + sin((M_PI * currPixel->h)/180);
        createHistogram(j,i);
        hist[j][i][floor(currPixel->h/10)]++;
//        printf("hist[%d][%d][%d] is %d \n",j,i,(int) floor(currPixel->h/10), hist[j][i][floor(currPixel->h/10)]);

      }else{
//        cout<< "stats 9"<< endl;
        // everything else
        sumSat[j][i] = sumSat[j-1][i] + sumSat[j][i-1] - sumSat[j-1][i-1] + currPixel->s;
        sumLum[j][i] = sumLum[j-1][i] + sumLum[j][i-1] - sumLum[j-1][i-1] + currPixel->l;
        sumHueX[j][i] = sumHueX[j-1][i] + sumHueX[j][i-1] - sumHueX[j-1][i-1] + cos((M_PI * currPixel->h)/180);
        sumHueY[j][i] = sumHueY[j-1][i] + sumHueY[j][i-1] - sumHueY[j-1][i-1] + sin((M_PI * currPixel->h)/180);
        createHistogram(j,i);
        hist[j][i][floor(currPixel->h/10)]++;
//        printf("hist[%d][%d][%d] is %d \n", j,i,(int)floor(currPixel->h/10), hist[j][i][floor(currPixel->h/10)]);
      }
    }
  }
//  cout<< "end of stats "<< endl;
}

//set up histogram for that point before adding
void stats::createHistogram(int x, int y){
  int rangeOfBins = 35;
  for(int k = 0; k < rangeOfBins; k++){
    if (x ==0){
      hist[x][y][k] = hist[x][y-1][k];
    }else if(y == 0){
      hist[x][y][k] = hist[x-1][y][k];
    }else {
      hist[x][y][k] = hist[x-1][y][k]+hist[x][y-1][k]-hist[x-1][y-1][k];
    }
  }
}

long stats::rectArea(pair<int,int> ul, pair<int,int> lr){

/* your code here */
long xTop = (long int) ul.first ;
//printf("xTop %d \n" , (int)xTop);
long yTop = (long int) ul.second ;
//printf("yTop %d \n" , (int)yTop);
long xBtm = (long int) lr.first ;
//printf("xBtm %d \n" , (int)xBtm);
long yBtm = (long int) lr.second;
//printf("yBtm %d \n" , (int)yBtm);
long area = (xBtm-xTop + 1) * (yBtm-yTop + 1) ;
//printf("area %d \n" , (int)area);
return area;
}

HSLAPixel stats::getAvg(pair<int,int> ul, pair<int,int> lr){

/* your code here */
//cout<<"start of getAvg" << endl;
long numPixel = rectArea(ul,lr);
//cout<<"getAvg 1" << endl;
int xTop = ul.first;
//cout<<"getAvg 2" << endl;
int yTop = ul.second;
//cout<<"getAvg 3" << endl;
int xBtm = lr.first;
//cout<<"getAvg 4" << endl;
int yBtm = lr.second;
//cout<<"getAvg 5" << endl;
HSLAPixel avgPixel;
//cout<<"getAvg 6" << endl;
double avgHue, avgSat, avgLum;
//cout<<"getAvg 7" << endl;

if(xTop == 0 && yTop == 0){
//  cout<< "getAvg 8" << endl;
  avgHue = atan2((sumHueY[xBtm][yBtm]),(sumHueX[xBtm][yBtm]))*180 /M_PI;
  avgSat = sumSat[xBtm][yBtm]/numPixel;
//  printf("sumLum[xBtm][yBtm] is %f and numPixel is %ld \n", sumLum[xBtm][yBtm], numPixel);
  avgLum = sumLum[xBtm][yBtm]/numPixel;
}else if (xTop == 0){
//  cout<< "getAvg 9" << endl;
  avgHue = atan2((sumHueY[xBtm][yBtm] - sumHueY[xTop][yTop-1]),
                        (sumHueX[xBtm][yBtm] - sumHueX[xTop][yTop-1]))*180 /M_PI;
  avgSat = (sumSat[xBtm][yBtm] - sumSat[xTop][yTop-1])/numPixel;
  avgLum = (sumLum[xBtm][yBtm] - sumLum[xTop][yTop-1])/numPixel;
}else if (yTop ==0){
//  cout<< "getAvg 10" << endl;
  avgHue = atan2((sumHueY[xBtm][yBtm] - sumHueY[xTop-1][yTop]),
                        (sumHueX[xBtm][yBtm] - sumHueX[xTop-1][yTop]))*180 /M_PI;
  avgSat = (sumSat[xBtm][yBtm] - sumSat[xTop-1][yTop])/numPixel;
  avgLum = (sumLum[xBtm][yBtm] - sumLum[xTop-1][yTop])/numPixel;
}else {
///  cout<< "getAvg 11" << endl;
  avgHue = atan2((sumHueY[xBtm][yBtm] - sumHueY[xTop-1][yTop] - sumHueY[xTop][yTop-1]),
                        (sumHueX[xBtm][yBtm] - sumHueX[xTop-1][yTop] - sumHueX[xTop][yTop-1]))*180 /M_PI;
  avgSat = (sumSat[xBtm][yBtm] - sumSat[xTop-1][yTop] - sumSat[xTop][yTop-1])/numPixel;
  avgLum = (sumLum[xBtm][yBtm] - sumLum[xTop-1][yTop] - sumLum[xTop][yTop-1])/numPixel;
}
//cout<< "getAvg 12" << endl;
return avgPixel = HSLAPixel(avgHue, avgSat, avgLum);
}

double stats::entropy(pair<int,int> ul, pair<int,int> lr){
//cout<< "start of entropy"<< endl;
    vector<int> distn;

    /* using private member hist, assemble the distribution over the
    *  given rectangle defined by points ul, and lr into variable distn.
    *  You will use distn to compute the entropy over the rectangle.
    *  if any bin in the distn has frequency 0, then do not add that
    *  term to the entropy total. see .h file for more details.
    */

    /* my code includes the following lines:
        if (distn[i] > 0 )
            entropy += ((double) distn[i]/(double) area)
                                    * log2((double) distn[i]/(double) area);
    */
    distn.resize(36);
//    cout<< " entropy 1"<< endl;
    int xTop = ul.first;
//    cout<< " entropy 2"<< endl;
    int yTop = ul.second;
//    cout<< " entropy 3"<< endl;
    int xBtm = lr.first;
//    cout<< " entropy 4"<< endl;
    int yBtm = lr.second;
//    cout<< " entropy 5"<< endl;
    int rangeOfColors = 36;
    double entropy = 0.0;
//    cout<< " entropy 6"<< endl;
    double area = (double) rectArea(ul,lr);
//    cout<< " entropy 7"<< endl;

    if(xTop == 0 && yTop == 0){
      cout<< " entropy 8"<< endl;
      for(int k = 0; k < rangeOfColors; k++){
//        cout<< "entropy loop 0 0 start"<< endl;
//        printf("hist[%d][%d][%d] is %d\n ",xBtm, yBtm,k, hist[xBtm][yBtm][k]);
        distn[k] = hist[xBtm][yBtm][k];
//        cout<< "entropy loop 0 0 end" << endl;
      }
    }else if(xTop == 0){
//    cout<< " entropy 9"<< endl;
      for(int k = 0; k < rangeOfColors; k++){
        distn[k] = hist[xBtm][yBtm][k] - hist[xBtm][yTop-1][k];
      }
    }else if(yTop == 0){
//      cout<< " entropy 10"<< endl;
      for(int k = 0; k < rangeOfColors; k++){
        distn[k] = hist[xBtm][yBtm][k] - hist[xBtm-1][yTop][k];
      }
    }else{
//      cout<< " entropy 11"<< endl;
      for(int k = 0; k < rangeOfColors; k++){
          distn[k] = hist[xBtm][yBtm][k] - hist[xTop-1][yTop][k] - hist[xTop][yTop-1][k] + hist[xTop+1][yTop+1][k];
      }
    }

    for(int i = 0; i < rangeOfColors; i++){
//      printf("entropy 12 loop %d\n", i );
      if (distn[i] > 0 )
          entropy += ((double) distn[i]/(double) area)
                                  * log2((double) distn[i]/(double) area);
    }
//    printf("entropy 13 end \n");
    return  -1 * entropy;
}
