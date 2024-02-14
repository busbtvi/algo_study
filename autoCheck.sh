#!/bin/bash
# find all untracked .cpp files and save as array
UntrackedCppFiles=(`git ls-files . --exclude-standard --others | grep \.cpp`)
# git change 되는건 감지 안됨
# ls -t

# if there are more than one untracked .cpp files, prompt user to select one
# if there are no untracked .cpp files, exit
if [ "${#UntrackedCppFiles[@]}" -gt 1 ]; then
    PS3="Select file to test: "
    select file in "${UntrackedCppFiles[@]}"
    do
        if [ $REPLY -gt "${#UntrackedCppFiles[@]}" ]; then
            echo "Invalid selection"
        else
            TargetFile=$file  
            break
        fi
    done
elif [ "${#UntrackedCppFiles[@]}" -eq 0 ]; then
    echo "No untracked .cpp files found"
    exit 1
else
    TargetFile=${UntrackedCppFiles[0]}
fi

# compile
# clang++ -std=c++17 -g $TargetFile -o ./target.out
TargetExe=${TargetFile%.cpp}.out

# get sample data
Url=`head -n 1 $TargetFile`
Url=${Url:3}
# -A "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/121.0.0.0 Safari/537.36"

# get HTML source, and extract sample data wrapped in <pre class="sampledata"></pre> tag
SampleData=`curl -s -A "Mozilla/5.0" $Url | awk '/<pre class=\"sampledata\"/,/<\/pre>/'`
# SampleData=`sed -n '/From/,/To/p'`
# https://mywiki.wooledge.org/BashFAQ/073

PRE_IFS=$IFS # 본래 IFS값을 백업해논다.
IFS=$'\t`'

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
        Result=`timeout 3s ./$TargetExe < sample.input`
        if [ $? -eq 124 ]; then 
            printf "\e[93m $CurrentTest: Timeout\n\e[0m"
            AllTestSuccess=false
        else 
            if [ -z `diff -w ./sample.output - <<< $Result` ]; then
                printf "\e[92m $CurrentTest: pass\n\e[0m"
            else
                printf "\e[91m $CurrentTest: fail\n\e[0m"
                AllTestSuccess=false
            fi
        fi
        ((CurrentTest++))
    fi
done

if [ $AllTestSuccess == true ]; then
    printf "\nAll tests passed\n"
else
    printf "\n\e[91mSome tests failed\e[0m\n"
fi
IFS=$PRE_IFS # IFS 원상 복구

# rm ./target.out
rm ./sample.input ./sample.output