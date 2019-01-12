#!/bin/bash

BIN="../ft_ssl"
GOOD=0
FAIL=0

X_exec()
{
    echo -e "-> $1"
    shared_ret=`bash -c "$1"`
}

ft_test()
{
    echo -e -n "\033[0;33m" "TEST: $1" "\033[0m"
    X_exec "$2"
    if [ "$3" = "$shared_ret" ]
    then
		GOOD=`expr $GOOD + 1`
        echo -e "\033[1;32m" "YES" "\033[0m"
    else
		FAIL=`expr $FAIL + 1`
        echo -e "\033[1;31m" "NO:\n" "-- expected:\n'$3'\n -- me:\n'$shared_ret'"  "\033[0m"
    fi

}

tests_md5()
{
    ft_test 'MD5 simple test' 'echo "pickle rick" | '$BIN' md5' 'c5e433c1dbd7ba01e3763a9483e74b04'
    ft_test 'MD5' 'echo "Do not pity the dead, Harry." | '$BIN' md5 -p' "Do not pity the dead, Harry.
2d95365bc44bf0a298e09a3ab7b34d2f"
    ft_test 'MD5' 'echo "Pity the living." | '$BIN' md5 -q -r' "e20c3b973f63482a778f3fd1869b7f25"
    X_exec 'echo "And above all," > file'
    ft_test 'MD5' ''$BIN' md5 file' "MD5 (file) = 53d53ea94217b259c11a5a2d104ec58a"
    ft_test 'MD5' ''$BIN' md5 -r file' '53d53ea94217b259c11a5a2d104ec58a file'
    ft_test 'MD5' ''$BIN' md5 -s "pity those that arent following baerista on spotify."' 'MD5 ("pity those that arent following baerista on spotify.") = a9946b1e1d9e55aea367b2e72399cbb4'
    ft_test 'MD5' 'echo "be sure to handle edge cases carefully" | '$BIN' md5 -p file' 'be sure to handle edge cases carefully
3553dc7dc5963b583c056d1b9fa3349c
MD5 (file) = 53d53ea94217b259c11a5a2d104ec58a'
    ft_test 'MD5' 'echo "some of this will not make sense at first" | '$BIN' md5 file' 'MD5 (file) = 53d53ea94217b259c11a5a2d104ec58a'
    ft_test 'MD5' 'echo "but eventually you will understand" | '$BIN' md5 -p -r file' 'but eventually you will understand
dcdd84e0f635694d2a943fa8d3905281
53d53ea94217b259c11a5a2d104ec58a file'
    ft_test 'MD5' 'echo "GL HF lets go" | '$BIN' md5 -p -s "foo" file' 'GL HF lets go
ab19110163d4af9f29d2181ba46a6c3a
MD5 ("foo") = acbd18db4cc2f85cedef654fccc4a4d8
MD5 (file) = 53d53ea94217b259c11a5a2d104ec58a'
    ft_test 'MD5' 'echo "one more thing" | '$BIN' md5 -r -p -s "foo" file -s "bar"' 'one more thing
a0bd1876c6f011dd50fae52827f445f5
acbd18db4cc2f85cedef654fccc4a4d8 "foo"
53d53ea94217b259c11a5a2d104ec58a file'
    ft_test 'MD5' 'echo "just to be extra clear" | '$BIN' md5 -r -q -p -s "foo" file' '3ba35f1ea0d170cb3b9a752e3360286c
acbd18db4cc2f85cedef654fccc4a4d8
53d53ea94217b259c11a5a2d104ec58a'
}

tests_sha256()
{
    ft_test 'SHA256 simple test' 'echo "pickle rick" | '$BIN' sha256' $(echo 'pickle rick' | shasum -a 256 | cut -d ' ' -f 1)
    ft_test 'SHA256' 'echo "Do not pity the dead, Harry." | '$BIN' sha256 -p' "Do not pity the dead, Harry.
$(echo 'Do not pity the dead, Harry.' | shasum -a 256 | cut -d ' ' -f 1)"
    ft_test 'SHA256' 'echo "Pity the living." | '$BIN' sha256 -q -r' "$(echo 'Pity the living.' | shasum -a 256 | cut -d ' ' -f 1)"
    X_exec 'echo "And above all," > file'
    ft_test 'SHA256' ''$BIN' sha256 file' "SHA256 (file) = $(echo 'And above all,' | shasum -a 256 | cut -d ' ' -f 1)"
    ft_test 'SHA256' ''$BIN' sha256 -r file' "$(echo 'And above all,' | shasum -a 256 | cut -d ' ' -f 1) file"
    ft_test 'SHA256' ''$BIN' sha256 -s "pity those that arent following baerista on spotify."' "SHA256 (\"pity those that arent following baerista on spotify.\") = $(echo -n 'pity those that arent following baerista on spotify.' | shasum -a 256 | cut -d ' ' -f 1)"
    ft_test 'SHA256' 'echo "be sure to handle edge cases carefully" | '$BIN' sha256 -p file' "be sure to handle edge cases carefully
$(echo 'be sure to handle edge cases carefully' | shasum -a 256 | cut -d ' ' -f 1)
SHA256 (file) = $(echo 'And above all,' | shasum -a 256 | cut -d ' ' -f 1)"
    ft_test 'SHA256' 'echo "some of this will not make sense at first" | '$BIN' sha256 file' "SHA256 (file) = $(echo 'And above all,' | shasum -a 256 | cut -d ' ' -f 1)"
    ft_test 'SHA256' 'echo "but eventually you will understand" | '$BIN' sha256 -p -r file' "but eventually you will understand
$(echo 'but eventually you will understand' | shasum -a 256 | cut -d ' ' -f 1)
$(echo 'And above all,' | shasum -a 256 | cut -d ' ' -f 1) file"
    ft_test 'SHA256' 'echo "GL HF lets go" | '$BIN' sha256 -p -s "foo" file' "GL HF lets go
$(echo 'GL HF lets go' | shasum -a 256 | cut -d ' ' -f 1)
SHA256 (\"foo\") = $(echo -n 'foo' | shasum -a 256 | cut -d ' ' -f 1)
SHA256 (file) = $(echo 'And above all,' | shasum -a 256 | cut -d ' ' -f 1)"
    ft_test 'SHA256' 'echo "one more thing" | '$BIN' sha256 -r -p -s "foo" file -s "bar"' "one more thing
$(echo 'one more thing' | shasum -a 256 | cut -d ' ' -f 1)
$(echo -n 'foo' | shasum -a 256 | cut -d ' ' -f 1) \"foo\"
$(echo 'And above all,' | shasum -a 256 | cut -d ' ' -f 1) file"
    ft_test 'SHA256' 'echo "just to be extra clear" | '$BIN' sha256 -r -q -p -s "foo" file' "$(echo 'just to be extra clear' | shasum -a 256 | cut -d ' ' -f 1)
$(echo -n 'foo' | shasum -a 256 | cut -d ' ' -f 1)
$(echo 'And above all,' | shasum -a 256 | cut -d ' ' -f 1)"
}

test_main() {
	tests_md5
	tests_sha256
	echo -e "" "\033[0;32m GOOD: $GOOD, \033[0;31m FAIL: $FAIL \033[0;33m, TOT:" `expr $GOOD + $FAIL` "\033[0m"
}

test_main