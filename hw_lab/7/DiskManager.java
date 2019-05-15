class DiskManager{
    Disk[] disks;
    int[] disksHead;
    static ResourceManager dRsM;
    public DiskManager(Disk[] d){
        disks = d;
        disksHead = new int[disks.length]; 
        dRsM = new ResourceManager(disks.length);
    }
    /*
    FileInfo WriteDiskFile(FileInfo fi, StringBuffer[] dataSet){
        int diskIndex = fi.disknumber;
        int startSector = fi.startingsector;
        int bufferLength = fi.fileLength;
        WriteDiskBlock(diskIndex, bufferLength, startSector, dataSet);
        FileInfo resfi = new FileInfo(diskIndex, startSector, bufferLength);
        return resfi;
    }
    */
    FileInfo WriteDiskFile(int count, String[] dataSet){
        int diskIndex = dRsM.request();
        int startSector = disksHead[diskIndex];
        int bufferLength = count;
        WriteDiskBlock(diskIndex, bufferLength, startSector, dataSet);
        FileInfo resfi = new FileInfo(diskIndex, startSector, bufferLength);
        dRsM.release(diskIndex);
        return resfi;
    }
    
    void WriteDiskBlock(int diskIndex, int bufferLength, int startSector, String[] dataSet){
        for(int i = 0; i < bufferLength; i++){
            StringBuffer sb = new StringBuffer(dataSet[i]);
            WriteDiskSector(diskIndex, startSector + i, sb);
        }
    }
    /*
    void WriteDiskBlock(int diskIndex, int bufferLength, int startSector, StringBuffer[] dataSet){
        for(int i = 0; i < bufferLength; i++){
            WriteDiskSector(diskIndex, startSector + i, dataSet[i]);
        }
    }
    */
    void WriteDiskSector(int diskIndex, int sector, StringBuffer data){
        disks[diskIndex].write(sector,data);
        disksHead[diskIndex]++;
    }

    StringBuffer[] ReadDiskFile(FileInfo fi){
        int diskIndex = fi.disknumber;
        int bufferLength = fi.fileLength;
        int startSector = fi.startingsector;
        StringBuffer[] dataSet = new StringBuffer[bufferLength];
        for (int i = 0; i < bufferLength; i++){
            dataSet[i] = new StringBuffer();
        }
        ReadDiskBlock(diskIndex, bufferLength, startSector, dataSet);
        return dataSet;
    }
    void ReadDiskBlock(int diskIndex, int bufferLength, int startSector, StringBuffer[] dataSet){
        for(int i = 0; i < bufferLength; i++){
            ReadDiskSector(diskIndex, startSector + i, dataSet[i]);
        }
    }
    void ReadDiskSector(int diskIndex, int sector, StringBuffer data){
        disks[diskIndex].read(sector,data);
    }
    public static void main(String[] args){
        Disk[] ds = new Disk[2];
        ds[0] = new Disk();
        ds[1] = new Disk();
        DiskManager dsm = new DiskManager(ds);
        FileInfo testfi = new FileInfo();
        testfi.disknumber = 1;
        testfi.fileLength = 3;
        testfi.startingsector = 1;
        StringBuffer[] dataSet = new StringBuffer[testfi.fileLength];
        dataSet[0] = new StringBuffer("test0");
        dataSet[1] = new StringBuffer("test1");
        dataSet[2] = new StringBuffer("test2");

        //dsm.WriteDiskFile(testfi, dataSet);
        StringBuffer[] dataSetRead = new StringBuffer[1];
        dataSetRead = dsm.ReadDiskFile(testfi);
        for(StringBuffer sb : dataSetRead){
            System.out.println(sb.toString());
        }
    }
}