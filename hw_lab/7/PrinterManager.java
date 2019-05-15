class PrinterManager{
    Printer[] printers;
    ResourceManager pRsM;
    int getprinterindex;
    public PrinterManager(Printer[] printers){
        this.printers = printers;
        pRsM = new ResourceManager(printers.length);
    }
    public Printer RequestPrinter(){
        return printers[pRsM.request()];
    }
    public void ReleasePrinter(Printer p) {
        for (int i = 0; i < printers.length; i++) {
            if (printers[i] == p) {
                pRsM.release(i);
            }
        }
    }

}