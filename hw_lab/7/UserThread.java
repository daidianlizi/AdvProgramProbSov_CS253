import java.io.BufferedReader;
import java.io.IOException;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;

class UserThread extends Thread{
    String curline;
    BufferedReader bufferreader;
    String parsefilename;
    int filecount;
    boolean issave = false;
    DiskManager dm;
    DirectoryManager drm;
    String[] cache;
    FileInfo fileinfo;
    PrinterManager pm;

    public UserThread(String username){
        try{
            bufferreader = new BufferedReader(new FileReader("USER/" + username));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    public void SetupDiskM(DiskManager dm){
        this.dm = dm;
    }
    public void SetupDirM(DirectoryManager drm){
        this.drm = drm;
    }
    public void SetupPrtM(PrinterManager pm){
        this.pm = pm;
    }
    boolean readcommand(){
        try{
            curline = bufferreader.readLine();
        } catch (IOException e){
            e.printStackTrace();
            return false;
        }
        if (curline == null)
            return false;
        //parse
        String[] curparse;
        curparse = curline.split(" ");
        if ( curparse[0].equals(".end") ){
            fileinfo = dm.WriteDiskFile(filecount, cache);
            issave = false;
            StringBuffer sb = new StringBuffer(parsefilename);
            drm.enter(sb, fileinfo);
            return true;
        }
        else if ( curparse[0].equals(".print") ){
            StringBuffer parsefilenamesb = new StringBuffer(curparse[1]);
            fileinfo = drm.lookup(parsefilenamesb);
            Printer printer = pm.RequestPrinter();
            PrintJobThread pjt = new PrintJobThread(fileinfo, printer);
            pjt.SetupPrtM(pm);
            pjt.SetupDiskM(dm);
            pjt.start();
            return true;
        }
        if (issave == false){
            if ( curparse[0].equals(".save") ){
                parsefilename = new String(curparse[1]);
                filecount = 0;
                issave = true;
                cache = new String[Disk.NUM_SECTORS];
                return true;
            }
        }
        else{
            cache[filecount] = new String(curline);
            filecount++;
            return true;
        }
        return false;
    }
    public void run(){
        while( readcommand());
        Thread.currentThread().interrupt();
    }
    public static void main(String[] args){
        Disk[] ds = new Disk[2];
        ds[0] = new Disk();
        ds[1] = new Disk();
        DiskManager dsm = new DiskManager(ds);
        //SetupDiskM(dsm);
        DirectoryManager drm = new DirectoryManager();
        //SetupDirM(drm);
        UserThread ut = new UserThread("USER1");
        ut.SetupDirM(drm);
        ut.SetupDiskM(dsm);
        ut.start();
    }
}