void reset(){
    curstate = 0;
    curindex[0] = 0;   
    for (int i = 0; i < 6; i++){
        values[i][0] = -1;
        values[i][1] = -1;
    }
}