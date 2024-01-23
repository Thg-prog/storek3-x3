package lab7;

import java.io.*;

public class WorkWithBinFile {
    void printFile(String filename, int skipCount, int endCount) {
        try (FileInputStream fileInputStream = new FileInputStream(filename)) {
            int data;
            int count = skipCount;
            fileInputStream.skip(skipCount);
            StringBuilder decryption = new StringBuilder(" ");
            while ((data = fileInputStream.read()) != -1 && count != endCount) {
                if (count % 16 == 0) {
                    System.out.printf("%08X: ", count);
                }
                System.out.printf("%02X ", data);
                if (data >= 32 && data <= 126) {
                    decryption.append(Character.toString(data));
                } else {
                    decryption.append('.');
                }
                count++;
                if (count % 8 == 0) {
                    System.out.print("  ");
                }
                if (count % 16 == 0) {
                    System.out.print(decryption);
                    decryption = new StringBuilder(" ");
                    System.out.println();
                }
            }
            if (count % 16 != 0) {
                System.out.println();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        WorkWithBinFile wwbf = new WorkWithBinFile();
        String filename = "190829_v29854.knp";
        System.out.println("Начало файла:");
        wwbf.printFile(filename, 0, 0x000210);
        System.out.println("\nКонец файла:");
        wwbf.printFile(filename, 0xd31000,  0);
    }
}