package main
import (
"fmt"
"os"
"strings"
"io/ioutil"
)

func getTextFromFile(filename string) (string, error) {
	file, err := os.Open(filename)
    if err != nil {
        return "", err
    }
    defer file.Close()
    content, err := ioutil.ReadAll(file)
    if err != nil {
        return "", err
    }
    return string(content), nil
}

func writeInfoIntoFile(text string, filename string) {
	file, err := os.Create(filename)
    if err != nil{
        fmt.Println("Unable to create file:", err) 
        os.Exit(1) 
    }
    defer file.Close() 
    file.WriteString(text)
}

func getDictWithEncryption() map[byte] byte {
	str1 := "bcdfghjklm"
	str2 := strings.ToUpper(str1)
	str3 := "zxwvtsrqpn"
	str4 := strings.ToUpper(str3)
	dict := map[byte] byte {}
	for i := 0; i < len(str1); i++ {
		dict[str1[i]] = str3[i]
		dict[str2[i]] = str4[i]
		dict[str3[i]] = str1[i]
		dict[str4[i]] = str2[i]
	}
	return dict
} 

func isConsonant(letter byte) bool {
	str := "bcdfghjklmzxwvtsrqpn"
	for _, value := range str {
		if strings.ToLower(string(letter)) == strings.ToLower(string(value)) {
			return true
		}
	}
	return false
}

func getEncryptedText(str string, dict map[byte] byte) string {
	for i := 0; i < len(str); i++ {
		if isConsonant(str[i]) {
			str = str[:i] + string(dict[str[i]]) + str[i+1:]
		}
	}
	return str
}

func main() {
	dict := getDictWithEncryption()
	str, err := getTextFromFile("cipher.txt")
	if err != nil {
        fmt.Println(err)
        return
    }
	str = getEncryptedText(str, dict)
	writeInfoIntoFile(str, "out.txt")
}