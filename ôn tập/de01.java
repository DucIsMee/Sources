import java.util.*;
import java.io.*;
public class de01{
    static void task1(){
        while(true){
            Random rd = new Random();
            int k =Math.abs(rd.nextInt());
            if(k%2021==0){System.out.println("Ket thuc!");break;}
            try{
                DataOutputStream out = new DataOutputStream(new FileOutputStream("data.dat"));
                out.writeInt(k);
                System.out.println("Da ghi so: " + k);
                out.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
            try{
                Thread.sleep(100);
            }catch (Exception c){
                c.printStackTrace();
            }
        }
    }
    public static void main(String[] args) {
        Thread t1 = new Thread(de01::task1);
        t1.start();
    }
}