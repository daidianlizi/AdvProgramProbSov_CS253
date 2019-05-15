import java.io.BufferedReader;
import java.io.IOException;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;

class PrintJobThread extends Thread{
    int disknumber;
    int startingsector;
    int fileLength;
    FileInfo fi;
    DiskManager dm;
    StringBuffer fileread;
    Printer printer;
    PrinterManager pm;

    public PrintJobThread(FileInfo fileinfo, Printer printer){
        fi = fileinfo;
        this.disknumber = fileinfo.disknumber;
        this.startingsector = fileinfo.startingsector;
        this.fileLength = fileinfo.fileLength;
        this.printer = printer;
    }
    public void SetupPrtM(PrinterManager pm){
        this.pm = pm;
    }
    public void run(){
        fileread = new StringBuffer();
        for (int i = 0; i < fileLength; i++){
            dm.ReadDiskSector(disknumber, startingsector + i, fileread);
            printer.print( fileread.toString() + "\n");
        }
        pm.ReleasePrinter(printer);
        Thread.currentThread().interrupt();
    }
    public void SetupDiskM(DiskManager dm){
        this.dm = dm;
    }
    public static void main(String[] agrs){
        Disk[] ds = new Disk[2];
        ds[0] = new Disk();
        ds[1] = new Disk();
        DiskManager dm = new DiskManager(ds);
        Printer printertest = new Printer("PRINTERTEST");
        FileInfo testfi = new FileInfo();
        testfi.disknumber = 1;
        testfi.fileLength = 3;
        testfi.startingsector = 1;
        StringBuffer[] dataSet = new StringBuffer[testfi.fileLength];
        dataSet[0] = new StringBuffer("test0");
        dataSet[1] = new StringBuffer("test1");
        dataSet[2] = new StringBuffer("test2");
        //dm.WriteDiskFile(testfi, dataSet);
        PrintJobThread pjt = new PrintJobThread(testfi, printertest);
        pjt.SetupDiskM(dm);
        pjt.start();
    }

}