package de11;
import java.io.*;
import java.net.*;
import java.util.Scanner;
import java.util.List;
import java.util.ArrayList;
public class de11cli{
    public static void main(String[] args) throws Exception{
        Socket s = new Socket("127.0.0.1",5000);
        DataOutputStream out = new DataOutputStream(s.getOutputStream());
        Scanner sc = new Scanner(System.in);
        System.out.print("Nhap n: ");
        int n = sc.nextInt();
        List<Double> a = new ArrayList<>();
        for(int i=0;i<n;i++){
            System.out.print("Nhap phan tu thu "+(i+1)+": ");
            Double t = sc.nextDouble();
            a.add(t);
        }
        out.writeInt(n);
        for(Double t : a){
            out.writeDouble(t);
        }
        out.flush();
        s.close();
        out.close();
    }
}