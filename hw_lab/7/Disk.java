class Disk{
    static final int NUM_SECTORS = 1024;
    StringBuffer sectors[] = new StringBuffer[NUM_SECTORS];
    void write(int sector, StringBuffer data){
        if (sectors[sector] == null) {
           sectors[sector] = new StringBuffer();
        }
        //sectors[sector].append(data);
        sectors[sector] = data;
        try{
            Thread.sleep(200);
        } catch (Exception e){

        }
    }
    void read(int sector, StringBuffer data){
        if (sectors[sector] == null)
            return;
        data.delete(0, data.length());
        //sectors[sector].append("goodgood");
        data.append(sectors[sector]);
        try{
            Thread.sleep(200);
        } catch (Exception e){

        }
    } // sleep
    public static void main(String[] args){
        Disk testdisk = new Disk();
        StringBuffer testdata = new StringBuffer("hello");
        testdisk.write(1, testdata);
        StringBuffer testread = new StringBuffer();
        testdisk.read(1, testread);
        System.out.println(testread.toString());
    }
}