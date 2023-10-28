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

func getTable(ar1 []string, ar2 []string) [][]string{
    arString := make([][]string, len(ar1))
    for i := range arString {
        arString[i] = make([]string, len(ar2))
    }
    for i := 0; i < len(ar1); i++ {
        flag := true
        for j := 0; j < len(ar2); j++ {
            if ar1[i] == ar2[j] && flag {
                arString[i][j] = "ok"
                flag = false
            } else {
                arString[i][j] = " "
            }
        }
    }
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
        flag := false
        for j := 0; j < len(ar2); j++ {
            if arString[0][j] == "ok" {
                flag = true
                break
            }
        }
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
    if len(ar2) != 0 {
        for j := len(ar2)-1; j >= 0; j-- {
            if arString[len(ar1)-1][j] == " " {
                arString[len(ar1)-1][j] = "a"
            } else {
                break
            }
        }
    }
    return arString
}

// // получение удалённых строк для c
// func getDeletedStrings(ar1 []string, ar2 []string, arString [][]string) map[int] string {
//     answer := map[int] string {}
//     ind := -1
//     for i := 0; i < len(ar1); i++ {
//         count := 0
//         for j := 0; j < len(ar2); j++ {
//             if arString[i][j] == "ok" {
//                 count++
//             }
//         }
//         if count == 0 {
//             answer[i+1] = "< " + ar1[i] + "\n"
//             ind = i+1
//         }
//     }
//     if ind != -1 {
//         answer[ind] += "...\n"
//     }
//     return answer
// }

// // получение добавленных строк для c
// func getAddedStrings(ar1 []string, ar2 []string, arString [][]string) map[int] string {
//     answer := map[int] string {}
//     for j := 0; j < len(ar2); j++ {
//         flag := false
//         for k := 0; k < len(ar1); k++ {
//             if arString[k][j] != " " {
//                 flag = true
//             }
//         }
//         if !flag {
//             answer[j+1] += "> " + ar2[j] + "\n"
//         }
//     }
//     return answer
// }

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
        answer[strconv.Itoa(len(ar1)) + "a" + strconv.Itoa(ind) + "," + strconv.Itoa(ind+count-1)] = str
    }
    return answer
}

func getC(ar1 []string, ar2 []string, arString [][]string) map[string] string {//getC(addedStrings map[int] string, deletedStrings map[int] string) map[int] string {
    // answer := map[int] string {}
    // key := 0
    // for addedKey := range addedStrings {
    //     for deletedKey := range deletedStrings {
    //         if addedKey == deletedKey {
    //             answer[addedKey] = deletedStrings[deletedKey]
    //             key = addedKey
    //         }
    //     }
    //     answer[key] += addedStrings[addedKey]
    // }
    // return answer
    answer := map[string] string {}
    ind := 0
    startInd := 1
    str := ""
    keys1 := []string {}
    // for key := range answer {
    //     //ar := strings.Split(key, ",")
    //     keys = append(keys, key) //ar[len(ar)-1])
    // }
    for i := 0; i < len(ar1); i++ {
        count := 0
        for j := 0; j < len(ar2); j++ {
            if arString[i][j] == "ok" {
                count++
            }
        }
        if count == 0 {
            if i - ind == 1 || i - ind == 0 {
                if str == "" {
                    startInd = i+1
                }
                str += "< " + ar1[i] + "\n"
            } else if i - ind > 1 {
                keys1 = append(keys1, strconv.Itoa(startInd) + "," + strconv.Itoa(i))
                answer[strconv.Itoa(i)] = str + "...\n"
                str = "< " + ar1[i] + "\n"
            }
            ind = i
        }
    }
    if str != "" && startInd != 1 {
        keys1 = append(keys1, strconv.Itoa(startInd) + "," + strconv.Itoa(ind+1))
        answer[strconv.Itoa(ind+1)] = str + "...\n"
    } else if str != "" && startInd == 1 {
        keys1 = append(keys1, strconv.Itoa(startInd))
        answer[strconv.Itoa(startInd)] = str + "...\n"
    }
    ind = 0
    startInd = 0
    str = ""
    keys2 := []string {}
    localResult := map[string] string {}
    for i := 0; i < len(ar2); i++ {
        flag := false
        for j := 0; j < len(ar1); j++ {
            if arString[j][i] != " " {
                flag = true
            }
        }
        if !flag {
            if i - ind == 1 || i - ind == 0 {
                if str == "" {
                    startInd = i+1
                }
                str += "> " + ar2[i] + "\n"
            } else if i - ind > 1 {
                //key = strconv.Itoa(startInd) + "," + strconv.Itoa(i)
                keys2 = append(keys2, strconv.Itoa(startInd) + "," + strconv.Itoa(i))
                localResult[strconv.Itoa(i)] = str + "...\n"
                str = "> " + ar2[i] + "\n"
            }
            ind = i
        }
    }
    if str != "" && startInd != 0 {
        keys2 = append(keys2, strconv.Itoa(startInd) + "," + strconv.Itoa(ind+1))
        localResult[strconv.Itoa(ind+1)] = str + "...\n"
    } else if str != "" && startInd == 0 {
        keys2 = append(keys2, strconv.Itoa(startInd))
        localResult[strconv.Itoa(startInd)] = str + "...\n"
    }
    result := map[string] string {}
    for i := 0; i < len(keys1); i++ {
        result[keys1[i] + "c" + keys2[i]] = answer[keys1[i]] + localResult[keys2[i]]
    }
    return result
}

func main() {
    values1, err1 := getTextFromFile("firstfile.txt")
	if err1 != nil {
        fmt.Println(err1)
        return
    }
    values2, err2 := getTextFromFile("secondfile.txt")
    if err2 != nil {
        fmt.Println(err2)
        return
    }
	ar1 := strings.Split(values1, "\n")
    ar1 = ar1[:len(ar1)-1]
    ar2 := strings.Split(values2, "\n")
    ar2 = ar2[:len(ar2)-1]
    arString := getTable(ar1, ar2)
    fmt.Println(arString)
    beginAddedStrings := getBeginAddedString(ar1, ar2, arString)
    // deletedStrings := getDeletedStrings(ar1, ar2, arString)
    // addedStrings := getAddedStrings(ar1, ar2, arString)
    // fmt.Println(deletedStrings)
    // fmt.Println(addedStrings)
    endAddedStrings := getEndAddedString(ar1, ar2, arString)
    changedStrings := getC(ar1, ar2, arString) //getC(addedStrings, deletedStrings)
    fmt.Println(beginAddedStrings)
    fmt.Println(changedStrings)
    fmt.Println(endAddedStrings)
}