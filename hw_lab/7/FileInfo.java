class FileInfo{
    int disknumber;
    int startingsector;
    int fileLength;
    public FileInfo(int disknumber, int startingsector, int fileLength){
        this.disknumber = disknumber;
        this.startingsector = startingsector;
        this.fileLength = fileLength;
    }
    public FileInfo(){
        
    }
}
