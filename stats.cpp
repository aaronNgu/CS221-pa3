
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
        hist[j][i][floor(currPixel->h/10)]++;
      }else if(j == 0){
        // left bottom pixel
        sumSat[j][i] = sumSat[j][i-1] + currPixel->s;
        sumLum[j][i] = sumLum[j][i-1] + currPixel->l;
        sumHueX[j][i] = sumLum[j][i-1] + cos((M_PI * currPixel->h)/180);
        sumHueY[j][i] = sumLum[j][i-1] + sin((M_PI * currPixel->h)/180);
        hist[j][i][floor(currPixel->h/10)]++;
      }else if(i == 0){
        // right top pixel
        sumSat[j][i] = sumSat[j-1][i] + currPixel->s;
        sumLum[j][i] = sumLum[j-1][i] + currPixel->l;
        sumHueX[j][i] = sumSat[j-1][i] + cos((M_PI * currPixel->h)/180);
        sumHueY[j][i] = sumSat[j-1][i] + sin((M_PI * currPixel->h)/180);
        hist[j][i][floor(currPixel->h/10)]++;
      }else{
        // everything else
        sumSat[j][i] = sumSat[j-1][i] + sumSat[j][i-1] + sumSat[j-1][i-1] + currPixel->s;
        sumLum[j][i] = sumSat[j-1][i] + sumSat[j][i-1] + sumSat[j-1][i-1] + currPixel->l;
        sumHueX[j][i] = sumSat[j-1][i] + sumSat[j][i-1] + sumSat[j-1][i-1] + cos((M_PI * currPixel->h)/180);
        sumHueY[j][i] = sumSat[j-1][i] + sumSat[j][i-1] + sumSat[j-1][i-1] + sin((M_PI * currPixel->h)/180);
        hist[j][i][floor(currPixel->h/10)]++;
      }

    }
  }
}

long stats::rectArea(pair<int,int> ul, pair<int,int> lr){

/* your code here */
long xUl = (long int) ul->first;
long yUl = (long int) ul->second;
long xLr = (long int) lr->first;
long yLr = (long int) lr->second;//??
long area = (xLr-xUl) * (yLr-xLr);
return area;
}

HSLAPixel stats::getAvg(pair<int,int> ul, pair<int,int> lr){

/* your code here */
long numPixel = rectArea(ul,lr);
int xTop = ul->first;
int yTop = ul->second;
int xBtm = lr->first;
int yBtm = lr->second;
HSLAPixel = avgPixel;

if(xTop == 0 && yTop == 0){
  double avgHue = atan(sumHueY[xBtm][yBtm]/sumHueX[xBtm][yBtm])*180 /M_PI;
  double avgSat = sumSat[xBtm][yBtm]/numPixel;
  double avgLum = sumLum[xBtm][yBtm]/numPixel;
}else if (xTop = 0){
  double avgHue = atan((sumHueY[xBtm][yBtm] - sumHueY[xTop][yTop-1])/
                        (sumHueX[xBtm][yBtm] - sumHueX[xTop][yTop-1]))*180 /M_PI;
  double avgSat = (sumSat[xBtm][yBtm] - sumSat[xTop][yTop-1])/numPixel;
  double avgLum = (sumLum[xBtm][yBtm] - sumLum[xTop][yTop-1])/numPixel;
}else if (yTop = 0){
  double avgHue = atan((sumHueY[xBtm][yBtm] - sumHueY[xTop-1][yTop])/
                        (sumHueX[xBtm][yBtm] - sumHueX[xTop-1][yTop]))*180 /M_PI;
  double avgSat = (sumSat[xBtm][yBtm] - sumSat[xTop-1][yTop])/numPixel;
  double avgLum = (sumLum[xBtm][yBtm] - sumLum[xTop-1][yTop])/numPixel;
}else {
  double avgHue = atan((sumHueY[xBtm][yBtm] - sumHueY[xTop-1][yTop] - sumHueY[xTop][yTop-1])/
                        (sumHueX[xBtm][yBtm] - sumHueX[xTop-1][yTop] - sumHueX[xTop][yTop-1]))*180 /M_PI;
  double avgSat = (sumSat[xBtm][yBtm] - sumSat[xTop-1][yTop] - sumSat[xTop][yTop-1])/numPixel;
  double avgLum = (sumLum[xBtm][yBtm] - sumLum[xTop-1][yTop] - sumLum[xTop][yTop-1])/numPixel;
}

return avgPixel = HSLAPixel(avgHue, avgSat, avgLum);
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
    double entropy;

    return  -1 * entropy;
}
