import java.io.*;
public class de01ct2{
    static void task2(){
        File f = new File("data.dat");
        while(true){
            try{
                DataInputStream in = new DataInputStream(new FileInputStream(f));
                int k = in.readInt();
                if(k%2021==0){System.out.println("Ket thuc!");break;}
                System.out.println("Da doc so: " + k);
                in.close();
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
    public static void main(String[] args){
        Thread t2 = new Thread(de01ct2::task2);
        t2.start();
    }
}