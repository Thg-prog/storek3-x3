package lab7;

import org.xml.sax.SAXException;

import javax.xml.parsers.ParserConfigurationException;
import java.io.*;
import java.util.HashMap;

public class ReadBinary {
    private final int SYSTEM_MESSAGE_PARAM = 0xffff;
    private InputStream inputStream;
    private BufferedWriter outputWriter;
    private HashMap<Integer, String> infoFromXML;
    private HashMap<Integer, String> infoFromIon;
    private int currentByte = 0;
    private String currentByteHex = "";
    private int codeLength = 0;
    private int valueType = 0;
    private long milliseconds = 0;
    private int paramNumber = 0;
    private int position = -1;
    private String buffString = "";
    private long usefulRecordsNum = 0;

    public ReadBinary(String _inputFilePath, String _outputFilePath, String pathXML, String pathIon) throws IOException, ParserConfigurationException, SAXException {
        inputStream = new FileInputStream(_inputFilePath);
        outputWriter = new BufferedWriter(new FileWriter(_outputFilePath));
        infoFromXML = ReadXML.getData(pathXML);
        infoFromIon = IonFileReader.getInfoFromIon(pathIon);
    }

    public void readAndWrite() throws IOException {
        while ((currentByte = inputStream.read()) != -1) {
            currentByteHex = String.format("%02x", currentByte);
            position++;
            switch (position) {
                case 0, 1:
                    checkParamNumber();
                    break;
                case 2, 3, 4, 5:
                    checkMilliseconds();
                    break;
                case 6:
                    checkMessageType();
                    break;
                case 7:
                    checkValueType();
                    break;
                default:
                    checkMessageValue();
                    break;
            }
        }
        System.out.println("TM fields: " + usefulRecordsNum);
        outputWriter.close();
    }

    private void checkParamNumber() throws IOException {
        if (position == 0) {
            buffString = currentByteHex;
        } else {
            buffString = buffString + currentByteHex;
            paramNumber = Integer.parseInt(buffString, 16);
            if (!isSystemMessage()) {
                String paramName = infoFromXML.get(paramNumber);
                outputWriter.write(paramName + ' ');
                outputWriter.write(Integer.toString(paramNumber) + ' ');
                usefulRecordsNum++;
            }
        }
    }

    private void checkMilliseconds() throws IOException {
        if (position == 2) {
            buffString = currentByteHex;
        } else {
            buffString += currentByteHex;
            if (position == 5) {
                milliseconds = Long.parseLong(buffString, 16);
                long seconds = milliseconds / 1000;
                long hours = seconds / 3600;
                long minutes = (seconds % 3600) / 60;
                seconds %= 60;

                if (!isSystemMessage())
                    outputWriter.write(String.format("%02d:%02d:%02d", hours, minutes, seconds) + ',' + milliseconds + ' ');
            }
        }
    }

    private void checkMessageType() throws IOException {
        if (!isSystemMessage() && infoFromIon.get(currentByte) != null) {
            outputWriter.write(infoFromIon.get(currentByte).strip() + ' ');
        }
    }

    private void checkValueType() {
        if (paramNumber == SYSTEM_MESSAGE_PARAM) {
            valueType = currentByte;
        } else {
            valueType = currentByte & 15;
        }
    }

    private void checkMessageValue() throws IOException {
        if (position == 8) {
            buffString = "";
        }
        switch (valueType) {
            case 0:
                getValueTypeLong();
                break;
            case 1:
                getValueTypeDouble();
                break;
            case 2:
                getValueTypeCode();
                break;
            case 3:
                getValueTypePoint();
                break;
        }
    }

    private void getValueTypeLong() throws IOException {
        if (position >= 8 && position <= 11) return;
        buffString += currentByteHex;
        if (position == 15) {
            if (!isSystemMessage()) {
                outputWriter.write(Long.toString(Long.parseLong(buffString, 16)));
                outputWriter.write('\n');
            }
            position = -1;
        }
    }

    private void getValueTypeDouble() throws IOException {
        buffString += currentByteHex;
        if (position == 15) {
            if (!isSystemMessage()) {
                try {
                    outputWriter.write(Double.toString(Double.longBitsToDouble(Long.parseLong(buffString, 16))));
                } catch (NumberFormatException e) {
                    outputWriter.write("Ошибка!!!");
                }
                outputWriter.write('\n');
            }
            position = -1;
        }
    }

    private void getValueTypeCode() throws IOException {
        if (position == 8 || position == 9) return;
        if (position == 10 || position == 11) {
            buffString += currentByteHex;
            if (position == 11) {
                codeLength = Integer.parseInt(buffString, 16);
                if (!isSystemMessage())
                    outputWriter.write("len:" + codeLength + ' ');
            }
        } else {
            if (position == 12) {
                buffString = "";
            }
            buffString += (String.format("%8s", Integer.toBinaryString(currentByte)).replace(' ', '0'));
            if (position == 15) {
                if (!isSystemMessage()) {
                    outputWriter.write(buffString.substring(buffString.length() - codeLength));
                    outputWriter.write('\n');
                }
                position = -1;
            }
        }
    }

    private void getValueTypePoint() throws IOException {
        if (position == 8 || position == 9) return;
        if (position == 10 || position == 11) {
            buffString = buffString + currentByteHex;
            if (position == 11) {
                codeLength = Integer.parseInt(buffString, 16);
                if (!isSystemMessage())
                    outputWriter.write("len:" + codeLength + ' ');
            }
        } else {
            if (--codeLength == 0) {
                if (!isSystemMessage()) {
                    outputWriter.write("point\n");
                }
                position = -1;
            }
        }
    }

    private boolean isSystemMessage()
    {
        return paramNumber == SYSTEM_MESSAGE_PARAM;
    }

    public static void main(String[] args) throws IOException, SAXException, ParserConfigurationException {
        ReadBinary binaryReader = new ReadBinary("190829_v29854.knp", "out.txt", "KNP-173.14.33.58.dat.xml.txt", "dimens.ion");
        binaryReader.readAndWrite();
    }
}