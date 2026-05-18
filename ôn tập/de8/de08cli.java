package de8;

import java.io.*;
import java.net.*;
import java.util.Random;

public class de08cli{
    public static void main(String[] args) throws Exception{
        Socket s = new Socket("127.0.0.1",5000);
        DataOutputStream out = new DataOutputStream(s.getOutputStream());
        Random rd = new Random();
        while(true){
            Double t = rd.nextDouble();
            if(t > 0.8 && t<0.82){
                System.out.println("Da tim duoc t = " + t);
                out.writeDouble(t);
                out.flush();
                break;
            }
        }
        s.close();
        out.close();
    }
}