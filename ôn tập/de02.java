import java.util.*;
public class de02{
    static volatile String st = "";
    static void task1(){
        Scanner sc = new Scanner(System.in);
        while(true){
            System.out.print("Nhap chuoi: ");
            st = sc.nextLine();
            if(st.equals("bye")){
                System.out.println("Ket thuc!");
                break;
            }
        }
        sc.close();
    }
    static void task2(){
        while(true){
            if(st.equals("bye")){
                System.out.println("Ket thuc!");
                break;
            }
            System.out.println("Da doc chuoi: " + st);
            try{
                Thread.sleep(1000);
            } catch(InterruptedException e){
                e.printStackTrace();
            }
        }
    }
    public static void main(String[] args) {
        Thread t1 = new Thread(de02::task1);
        Thread t2 = new Thread(de02::task2);
        t1.start();
        t2.start();
    }
}