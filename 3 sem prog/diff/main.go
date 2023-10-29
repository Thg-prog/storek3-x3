package main
import (
"fmt"
"os"
"io/ioutil"
"strings"
"strconv"
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

func getValueOfFlag(length int, ind int, what string, arString [][]string) bool {
    flag := false
    for i := 0; i < length; i++ {
        if arString[ind][i] == what {
            return true
        }
    }
    return flag
}

func getValueOfFlagReverse(length int, ind int, what string, arString [][]string) bool {
    flag := false
    for i := 0; i < length; i++ {
        if arString[i][ind] != what {
            return true
        }
    }
    return flag
}

func spaceFlagHandle(ar []string) {
    for i := 0; i < len(ar); i++ {
        str := strings.Split(ar[i], " ")
        val := ""
        for j := 0; j < len(str); j++ {
            val += str[j]
        }
        ar[i] = val
    }
}

func registerFlagHandle(ar []string) {
    for i := 0; i < len(ar); i++ {
        ar[i] = strings.ToLower(ar[i])
    }
}

func getTable(_ar1 []string, _ar2 []string, inputFlag string) [][]string {
    ar1 := make([]string, len(_ar1))
    ar2 := make([]string, len(_ar2))
    copy(ar1, _ar1[:])
    copy(ar2, _ar2[:])
    arString := make([][]string, len(ar1))
    for i := range arString {
        arString[i] = make([]string, len(ar2))
    }
    if inputFlag == "-b" {
        spaceFlagHandle(ar1)
        spaceFlagHandle(ar2)
    } else if inputFlag == "-i" {
        registerFlagHandle(ar1)
        registerFlagHandle(ar2)
    }
    // отметка о равенстве строки из первого и второго файла (для c)
    for i := 0; i < len(ar1); i++ {
        flag := true
        for j := 0; j < len(ar2); j++ {
            if ar1[i] == ar2[j] && flag && ar1[i] != "" {
                flag = false
                arString[i][j] = "ok"
            } else {
                arString[i][j] = " "
            }
        }
    }
    // проверка на "правильность" таблицы, то есть проверка на диагональный вид ok (для c)
    for i := 0; i < len(ar1); i++ {
        for j := 0; j < len(ar2); j++ {
            if arString[i][j] == "ok" {
                flag := true
                for n := i+1; n < len(ar1); n++ {
                    for m := 0; m <= j; m++ {
                        if arString[n][m] == "ok" {
                            flag = false
                        }
                    }
                }
                if !flag {
                    arString[i][j] = " "
                }
            }
        }
    }

    // для a, которые будут в начале
    if len(ar1) != 0 {
        ind := -1
        for j := 0; j < len(ar2); j++ {
            for i := 0; i < len(ar1); i++ {
                if arString[i][j] == "ok" {
                    ind = j
                    break
                }
            }
            if ind != -1 {
                break
            }
        }
        flag := getValueOfFlag(len(ar2), 0, "ok", arString)
        if flag && ind != -1 {
            for j := 0; j < ind; j++ {
                if arString[0][j] == " " {
                    arString[0][j] = "a"
                } else {
                    break
                }
            }
        }
    }

    // для a, которые будут в конце
    if len(ar2) != 0 {
        flag := getValueOfFlag(len(ar2), len(ar1)-1, "ok", arString)
        if flag {
            for j := len(ar2)-1; j >= 0; j-- {
                if arString[len(ar1)-1][j] == " " { 
                    flag = getValueOfFlagReverse(len(ar1), j, " ", arString)
                    if !flag {
                        arString[len(ar1)-1][j] = "a"
                    }
                } else {
                    break
                }
            }
        }
    }
    return arString
}

// получение добавленных строк в начало для а
func getBeginAddedString(ar1 []string, ar2 []string, arString [][]string) map[string] string { 
    str := ""
    count := 0
    for j := 0; j < len(ar2); j++ {
        if arString[0][j] == "a" {
            str += "> " + ar2[j] + "\n"
            count += 1
        } else {
            break
        }
    }
    answer := map[string] string {}
    if str != "" {
        answer[strconv.Itoa(0) + "a" + strconv.Itoa(1) + "," + strconv.Itoa(count)] = str
    }
    return answer
}

// получение добавленных строк в конец для а
func getEndAddedString(ar1 []string, ar2 []string, arString [][]string) map[string] string {
    str := ""
    ind := -1
    count := 0
    for j := 0; j < len(ar2); j++ {
        if arString[len(ar1)-1][j] == "a" {
            str += "> " + ar2[j] + "\n"
            ind = j
            count += 1
        }
    }
    answer := map[string] string {}
    if str != "" {
        answer[strconv.Itoa(len(ar1)) + "a" + strconv.Itoa(ind-count+2) + "," + strconv.Itoa(ind+1)] = str
    }
    return answer
}

// проход по таблице 
func getResultForC(ar1 []string, ar2 []string, what string, sign string, arString [][]string) (map[string] string, []string) {
    result := map[string] string {}
    ind := 0
    startInd := 0
    str := ""
    keys := []string {}
    for i := 0; i < len(ar1); i++ {
        flag := false 
        if sign == "<" {
            flag = getValueOfFlag(len(ar2), i, what, arString)
        } else {
            flag = getValueOfFlagReverse(len(ar2), i, what, arString)
        }
        if !flag {
            if i - ind == 1 || i - ind == 0 {
                if str == "" {
                    startInd = i+1
                }
                str += sign + " " + ar1[i] + "\n"
            } else if i - ind > 1 {
                if str != "" {
                    if str[len(str)-3] == sign[0] {
                        str = str[:len(str)-4] + "\n"
                        ind--
                    }
                    keys = append(keys, strconv.Itoa(startInd) + "," + strconv.Itoa(ind+1))
                    if sign == "<" {
                        str = str + "...\n"
                    }
                    result[strconv.Itoa(startInd) + "," + strconv.Itoa(ind+1)] = str
                }
                startInd = i+1
                str = sign + " " + ar1[i] + "\n"
            }
            ind = i
        }
    }
    if str != "" && startInd != 0 {
        keys = append(keys, strconv.Itoa(startInd) + "," + strconv.Itoa(ind+1))
        if sign == "<" {
            str = str + "...\n"
        }
        result[strconv.Itoa(startInd) + "," + strconv.Itoa(ind+1)] = str
    } else if str != "" && startInd == 0 {
        keys = append(keys, strconv.Itoa(startInd))
        if sign == "<" {
            str = str + "...\n"
        }
        result[strconv.Itoa(startInd)] = str
    }
    return result, keys
}

func getVal(key string) string {
    val := key
    splitKey := strings.Split(key, ",")
    if len(splitKey) > 1 && splitKey[0] == splitKey[1] {
        conv, _ := strconv.Atoi(splitKey[0])
        val = strconv.Itoa(conv)
    }
    return val
}

func getC(ar1 []string, ar2 []string, arString [][]string) map[string] string {
    localResult1, keys1 := getResultForC(ar1, ar2, "ok", "<", arString)
    localResult2, keys2 := getResultForC(ar2, ar1, " ", ">", arString)
    result := map[string] string {}
    if len(keys1) == len(keys2) {
        for i := 0; i < len(keys1); i++ {
            val1 := getVal(keys1[i])
            val2 := getVal(keys2[i])
            result[val1 + "c" + val2] = localResult1[keys1[i]] + localResult2[keys2[i]]
        }
    } else {
        for i := 0; i < len(keys1); i++ {
            splitKey := strings.Split(keys1[i], ",")
            conv, _ := strconv.Atoi(splitKey[0])
            if len(splitKey) > 1 && splitKey[0] == splitKey[1] {
                result[strconv.Itoa(conv) + "d" + strconv.Itoa(conv-1)] = localResult1[keys1[i]][:len(localResult2[keys1[i]])-4]
            } else {
                result[keys1[i] + "d" + strconv.Itoa(conv-1)] = localResult1[keys1[i]][:len(localResult1[keys1[i]])-4]
            }
        }
    }
    return result
}

func sort(dict map[string] string) []string{
    keys := []string {}
    for key := range dict {
        keys = append(keys, key)
    }
    for i := 0; i < len(keys)-1; i++ {
        for j := 0; j < len(keys)-1-i; j++ {
            key1, _ := strconv.Atoi(strings.Split(strings.Split(keys[j], "c")[0], ",")[0])
            key2, _ := strconv.Atoi(strings.Split(strings.Split(keys[j+1], "c")[0], ",")[0])
            if key1 > key2 {
                keys[j], keys[j+1] = keys[j+1], keys[j]
            }
        }
    }
    return keys
}

func main() {
    values1, err1 := getTextFromFile(os.Args[1])
	if err1 != nil {
        fmt.Println(err1)
        return
    }
    values2, err2 := getTextFromFile(os.Args[2])
    if err2 != nil {
        fmt.Println(err2)
        return
    }
    flag := ""
    if len(os.Args) == 4 {
        flag = os.Args[3]
    }
	ar1 := strings.Split(values1, "\n")
    ar1 = ar1[:len(ar1)-1]
    ar2 := strings.Split(values2, "\n")
    ar2 = ar2[:len(ar2)-1]
    arString := getTable(ar1, ar2, flag)
    beginAddedStrings := getBeginAddedString(ar1, ar2, arString)
    endAddedStrings := getEndAddedString(ar1, ar2, arString)
    changedStrings := getC(ar1, ar2, arString)
    for key := range beginAddedStrings {
        fmt.Print(key + "\n")
        fmt.Print(beginAddedStrings[key])
    }
    keys := sort(changedStrings)
    for _, key := range keys {
        fmt.Print(key + "\n")
        fmt.Print(changedStrings[key])
    }
    for key := range endAddedStrings {
        fmt.Print(key + "\n")
        fmt.Print(endAddedStrings[key])
    }
}