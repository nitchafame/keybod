
//----- Simple lowpass filter
// requires recycling the output in the "smoothedVal" param

int smooth(int data, float filterVal, float smoothedVal) {

  filterVal = constrain(filterVal, 0, 0.999999);
  smoothedVal = (data * (1 - filterVal)) + (smoothedVal  *  filterVal);
  return (int)smoothedVal;
}
