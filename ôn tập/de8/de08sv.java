package de8;

import java.io.*;
import java.net.*;

public class de08sv{
    public static void main(String[] args) throws Exception{
        ServerSocket ss = new ServerSocket(5000);
        System.out.println("Server dang ket noi...");
        Socket s = ss.accept();
        System.out.println("Server da ket noi voi client!");
        DataInputStream in = new DataInputStream(s.getInputStream());
        Double min = Double.MIN_VALUE;
        while(true){
            Double t = in.readDouble();
            System.out.println("Da nhan duoc t = " + t);
            if(t > 0.8 && t < 0.82){
                System.out.println("t thuoc khoang (0.8-0.82),ket thuc!");
                break;
            }
            if(min==Double.MIN_VALUE || min>t){
                min=t;
            }
        }
        System.out.println("Gia tri nho nhat trong khoang (0.8-0.82) la: " + min);
        ss.close();
        s.close();
        in.close();

    }
}