import java.io.*;
import java.net.*;
import java.util.Random;

public class de05cli {
    public static void main(String[] args) throws Exception {
        Socket s= new Socket("127.0.0.1",5000);
        DataOutputStream out = new DataOutputStream(s.getOutputStream());
        Random rand = new Random();
        int k;
        do{
            k = rand.nextInt(20000);
            System.out.println("Gui: " + k);
            out.writeInt(k);
            out.flush();
            Thread.sleep(1000);
        }while(!(k>10000 && k%2022 ==0));
        out.close();
        s.close();
    }
}