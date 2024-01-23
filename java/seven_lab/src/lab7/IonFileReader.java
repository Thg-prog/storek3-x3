package lab7;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;

public class IonFileReader {
        public static HashMap<Integer, String> getInfoFromIon(String filename) throws IOException {
            HashMap<Integer, String> arr = new HashMap<Integer,String>();
            BufferedReader reader = new BufferedReader(new FileReader(filename));
            String line;
            int num = 1;
            while((line = reader.readLine()) != null) {
                if(line.length()>1)
                    arr.put(num, line);
                num++;
            }
            reader.close();
            return arr;
        }
}
