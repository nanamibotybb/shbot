for i in $1/*
do
    grep \"memberName\" $i
    grep -A 1 \"sender\" $i | grep \"id\"
    grep \"text\" $i
    grep \"nickname\" $i
    grep \"name\" $i
    echo 
done
