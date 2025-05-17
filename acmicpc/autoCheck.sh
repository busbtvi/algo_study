#!/bin/bash
function compile(){
    clang++ -std=c++17 $1.cpp -o $1
}

# find the latest cpp file
UntrackedCppFiles=(`ls -t | grep \.cpp`)

# check user wants to test the latest cpp file
read -p "Check ${UntrackedCppFiles[0]} [(default)y / n] : " yn
case $yn in
    [Nn]* )
        PS3="Select file to test : "
        select file in "${UntrackedCppFiles[@]}"
        do
            if [ $REPLY -gt "${#UntrackedCppFiles[@]}" ]; then
                echo "Invalid selection"
            else
                TargetFile=$file  
                break
            fi
        done;;
    * ) 
        TargetFile=${UntrackedCppFiles[0]};;
esac

TargetFile=${TargetFile%.cpp}

# compile
if [ -f $TargetFile ]; then
    # check if the cpp file is newer than the executable
    cppFileTime=$(date -r $TargetFile.cpp +%s)
    outFileTime=$(date -r $TargetFile +%s)
    if [ $cppFileTime -gt $outFileTime ]; then
        printf "\e[93mSource code modified. recompile $TargetFile.cpp\n\e[0m"
        compile $TargetFile
    fi
else
    printf "\e[93mNo Executablbe file. compiling $TargetFile.cpp\n\e[0m"
    compile $TargetFile
fi
TargetExe=$TargetFile

# get sample data
Url=`head -n 1 $TargetFile.cpp`
Url=${Url:3}
# -A "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/121.0.0.0 Safari/537.36"

# get HTML source, and extract sample data wrapped in <pre class="sampledata"></pre> tag
SampleData=`curl -s -A "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7)" $Url | awk '/<pre class=\"sampledata\"/,/<\/pre>/'`
# SampleData=`sed -n '/From/,/To/p'`
# https://mywiki.wooledge.org/BashFAQ/073

PRE_IFS=$IFS # 본래 IFS값을 백업해논다.
IFS=$'\t`'

# sample data doesn't have answer..
# check at parents directory
# if [ -f "../local.sample" ]; then
#     SampleData+="$(cat ../local.sample)"
# fi

CurrentMode="none"
CurrentTest=1
AllTestSuccess=true
touch ./sample.input
touch ./sample.output

for word in $SampleData; do
    if [[ $word == *"output"* ]]; then
        CurrentMode="output"
    else CurrentMode="input"
    fi

    word=`echo $word | cut -d '>' -f 2 | cut -d '<' -f 1`
    echo $word > ./sample.$CurrentMode

    if [ $CurrentMode == "output" ]; then
        Result=`gtimeout 3s ./$TargetExe < sample.input`
        if [ $? -eq 124 ]; then 
            printf "\e[93m $CurrentTest: Timeout\n\e[0m"
            AllTestSuccess=false
        else 
            if [ -z `diff -w ./sample.output - <<< $Result` ]; then
                printf "\e[92m $CurrentTest: pass\n\e[0m"
            else
                printf "\e[91m $CurrentTest: fail\n\e[0m"
                echo "----- Input -----"
                cat ./sample.input
                echo "----- Expected -----"
                cat ./sample.output
                echo "----- Result -----"
                echo $Result
                AllTestSuccess=false
            fi
        fi
        ((CurrentTest++))
    fi
done

IFS=$PRE_IFS # IFS 원상 복구

if [ $AllTestSuccess == true ]; then
    printf "\n\e[92mAll tests passed\n\e[0m"
else
    printf "\n\e[91mSome tests failed\e[0m"
fi

# rm ./target.out
rm ./sample.input ./sample.output