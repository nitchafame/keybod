
//----- Simple lowpass filter
// requires recycling the output in the "smoothedVal" param

int smooth(int data, float filterVal, float smoothedVal) {

  if (filterVal > 1) {     // check to make sure param's are within range
    filterVal = .999999;
  }
  else if (filterVal <= 0) {
    filterVal = 0;
  }
  
  smoothedVal = (data * (1 - filterVal)) + (smoothedVal  *  filterVal);
  return (int)smoothedVal;
}
