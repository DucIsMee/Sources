import java.io.*;
import java.net.*;

public class de05sv{
    public static void main(String[] args) throws Exception {
        ServerSocket ss = new ServerSocket(5000);
        System.out.println("Server dang cho ket noi...");
        Socket s = ss.accept();
        System.out.println("Server da ket noi voi client!");
        DataInputStream in = new DataInputStream(s.getInputStream());
        int max =0;
        while(true){
            int k = in.readInt();
            if(k>10000 && k%2022==0){
                System.out.println("Nhan duoc so: " + k);
                break;
            }
            if (k>max) max = k;
            System.out.println("Max hien tai: "+ max);
        }
        in.close();
        s.close();
        ss.close();
    }
}