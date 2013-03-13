for i in {10..500..10}
do
    let "c = $i * $i"
    echo $c `./foo $i`
done
