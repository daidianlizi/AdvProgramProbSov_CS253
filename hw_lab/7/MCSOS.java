class MCSOS {
    static final int NUMBER_OF_USERS=4;
    static final int NUMBER_OF_DISKS=2;
    static final int NUMBER_OF_PRINTERS=3;
    static UserThread[] users = new UserThread[NUMBER_OF_USERS];
    static Printer[] printers = new Printer[NUMBER_OF_PRINTERS];
    static Disk[] disks = new Disk[NUMBER_OF_DISKS];
    static DiskManager dm;
    static PrinterManager pm;
    static DirectoryManager drm;
    
    static void ConstructDevices(){
        for (int i = 0; i < NUMBER_OF_USERS; i++){
            users[i] = new UserThread("USER"+(i+1));
        }
        for (int i = 0; i < NUMBER_OF_PRINTERS; i++){
            printers[i] = new Printer("PRINTER"+(i+1));
        }
        for (int i = 0; i < NUMBER_OF_DISKS; i++){
            disks[i] = new Disk();
        }
    }
    static void ConstructManagers(){
        dm = new DiskManager(disks);
        drm = new DirectoryManager();
        pm = new PrinterManager(printers);
        for (int i = 0; i < NUMBER_OF_USERS; i++){
            users[i].SetupDirM(drm);
            users[i].SetupDiskM(dm);
            users[i].SetupPrtM(pm);
        }
    }
    public static void main(String[] args){
        ConstructDevices();
        ConstructManagers();
        for (int i = 0; i < NUMBER_OF_USERS; i++){
            users[i].start();
        }
    }
}
