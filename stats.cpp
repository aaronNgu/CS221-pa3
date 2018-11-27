
#include "stats.h"

stats::stats(PNG & im){

/* your code here! */
  //sumLum, sumSat, sumHueX, sumHueY

  HSLAPixel* currPixel;
  for(int i = 0; i < img.height(); i++){
    for(int j = 0; j < img.width(); j++){
      currPixel = im.getPixel(j,i);

      if(i == 0 && j == 0){
        // starting pixel
        sumSat[j][i] = currPixel->s;
        sumLum[j][i] = currPixel->l;
        sumHueX[j][i] = cos((M_PI * currPixel->h)/180);
        sumHueY[j][i] = sin((M_PI * currPixel->h)/180);
      }else if(j == 0){
        // left bottom pixel
        sumSat[j][i] = sumSat[j][i-1] + currPixel->s;
        sumLum[j][i] = sumLum[j][i-1] + currPixel->l;
        sumHueX[j][i] = sumLum[j][i-1] + cos((M_PI * currPixel->h)/180);
        sumHueY[j][i] = sumLum[j][i-1] + sin((M_PI * currPixel->h)/180);
      }else if(i == 0){
        // right top pixel
        sumSat[j][i] = sumSat[j-1][i] + currPixel->s;
        sumLum[j][i] = sumLum[j-1][i] + currPixel->l;
        sumHueX[j][i] = sumSat[j-1][i] + cos((M_PI * currPixel->h)/180);
        sumHueY[j][i] = sumSat[j-1][i] + sin((M_PI * currPixel->h)/180);
      }else{
        // everything else
        sumSat[j][i] = sumSat[j-1][i] + sumSat[j][i-1] + sumSat[j-1][i-1] + currPixel->s;
        sumLum[j][i] = sumSat[j-1][i] + sumSat[j][i-1] + sumSat[j-1][i-1] + currPixel->l;
        sumHueX[j][i] = sumSat[j-1][i] + sumSat[j][i-1] + sumSat[j-1][i-1] + cos((M_PI * currPixel->h)/180);
        sumHueY[j][i] = sumSat[j-1][i] + sumSat[j][i-1] + sumSat[j-1][i-1] + sin((M_PI * currPixel->h)/180);
      }

    }
  }

  //vector<vector<vector<int>>> hist;
}

long stats::rectArea(pair<int,int> ul, pair<int,int> lr){

/* your code here */


}

HSLAPixel stats::getAvg(pair<int,int> ul, pair<int,int> lr){

/* your code here */

}

double stats::entropy(pair<int,int> ul, pair<int,int> lr){

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

    return  -1 * entropy;
}
