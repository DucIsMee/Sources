package de11;
import java.io.*;
import java.net.*;
import java.util.List;
import java.util.ArrayList;
public class de11sv {
    public static void main(String[] args) throws Exception{
        ServerSocket ss = new ServerSocket(5000);
        System.out.println("Server dang ket noi toi client!");
        Socket s = ss.accept();
        System.out.println("Server da ket noi toi client");
        DataInputStream in = new DataInputStream(s.getInputStream());
        int n = in.readInt();
        if(n<=0) {
            System.out.println("N phai lon hon 0! Ket thuc!");
            return;
        }
        else{
            List<Double> a = new ArrayList<>();
            System.out.print("Mang da nhap: ");
            for(int i=0;i<n;i++){
                Double t = in.readDouble();
                a.add(t);
                System.out.print(" " + t);
            }
            Double sum = 0.0;
            for(Double i : a){
                sum+=i;
            }
            System.out.println();
            System.out.println("TBC = "+sum/n);
        }
        in.close();
        ss.close();
        s.close();
    }
}