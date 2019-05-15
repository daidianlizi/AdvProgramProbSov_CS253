import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class Printer{
    String prtfile;
    public Printer(String str){
        prtfile = str;
    }
    //Path pathfile = Paths.get("./", prtfile);
    //File file = new File(path);
    //File file = new File("./test");
    //if (!file.exists()) {
    //    file.createNewFile();
    //}

    void print(String writerContent){
        try{
            FileWriter writer = new FileWriter("PRINTER/" + prtfile, true);// 获取该文件的输出流,关键字true表示追加
            writer.write(writerContent);// 写内容
            writer.flush();// 清空缓冲区，立即将输出流里的内容写到文件里
            writer.close();// 关闭输出流，release资源
        } catch (Exception e){
            e.printStackTrace();
        }
        try {
            Thread.sleep(2750);
        } catch (Exception e) {

        }

    } // sleeps
    public static void main(String[] args){
        Printer PRINTERTEST  = new Printer("PRINTERTEST");
        String writerContent = "hello world";
        PRINTERTEST.print(writerContent);
    }
}
