#!/bin/bash

# Setup
echo "And above all," > file

PASS=0
FAIL=0

check() {
    local desc="$1"
    local got="$2"
    local expected="$3"

    if [ "$got" = "$expected" ]; then
        echo "[OK]  $desc"
        PASS=$((PASS + 1))
    else
        echo "[KO]  $desc"
        echo "      expected: $expected"
        echo "      got:      $got"
        FAIL=$((FAIL + 1))
    fi
}

# stdin
check "stdin basic" \
    "$(echo "42 is nice" | ./ft_ssl md5)" \
    "(stdin)= 35f1d6de0302e2086a4e472266efb3a9"

# -p
check "-p" \
    "$(echo "42 is nice" | ./ft_ssl md5 -p)" \
    '("42 is nice")= 35f1d6de0302e2086a4e472266efb3a9'

# -q -r
check "-q -r" \
    "$(echo "Pity the living." | ./ft_ssl md5 -q -r)" \
    "e20c3b973f63482a778f3fd1869b7f25"

# file
check "file" \
    "$(./ft_ssl md5 file)" \
    "MD5 (file) = 53d53ea94217b259c11a5a2d104ec58a"

# -r file
check "-r file" \
    "$(./ft_ssl md5 -r file)" \
    "53d53ea94217b259c11a5a2d104ec58a file"

# -s
check "-s" \
    "$(./ft_ssl md5 -s "pity those that aren't following baerista on spotify.")" \
    "MD5 (\"pity those that aren't following baerista on spotify.\") = a3c990a1964705d9bf0e602f44572f5f"

# -p file
check "-p file" \
    "$(echo "be sure to handle edge cases carefully" | ./ft_ssl md5 -p file)" \
    "$(printf '("be sure to handle edge cases carefully")= 3553dc7dc5963b583c056d1b9fa3349c\nMD5 (file) = 53d53ea94217b259c11a5a2d104ec58a')"

# stdin ignored with file
check "stdin ignored with file" \
    "$(echo "some of this will not make sense at first" | ./ft_ssl md5 file)" \
    "MD5 (file) = 53d53ea94217b259c11a5a2d104ec58a"

# -p -r file
check "-p -r file" \
    "$(echo "but eventually you will understand" | ./ft_ssl md5 -p -r file)" \
    "$(printf '("but eventually you will understand")= dcdd84e0f635694d2a943fa8d3905281\n53d53ea94217b259c11a5a2d104ec58a file')"

# -p -s file
check "-p -s file" \
    "$(echo "GL HF let's go" | ./ft_ssl md5 -p -s "foo" file)" \
    "$(printf '("GL HF let'"'"'s go")= d1e3cc342b6da09480b27ec57ff243e2\nMD5 ("foo") = acbd18db4cc2f85cedef654fccc4a4d8\nMD5 (file) = 53d53ea94217b259c11a5a2d104ec58a')"

# -r -p -s file -s bar (bar after file → error)
check "-r -p -s foo file -s bar" \
    "$(echo "one more thing" | ./ft_ssl md5 -r -p -s "foo" file -s "bar" 2>&1)" \
    "$(printf '("one more thing")= a0bd1876c6f011dd50fae52827f445f5\nacbd18db4cc2f85cedef654fccc4a4d8 "foo"\n53d53ea94217b259c11a5a2d104ec58a file\nft_ssl: md5: -s: No such file or directory\nft_ssl: md5: bar: No such file or directory')"

# -r -q -p -s foo file
check "-r -q -p -s foo file" \
    "$(echo "just to be extra clear" | ./ft_ssl md5 -r -q -p -s "foo" file)" \
    "$(printf 'just to be extra clear\n3ba35f1ea0d170cb3b9a752e3360286c\nacbd18db4cc2f85cedef654fccc4a4d8\n53d53ea94217b259c11a5a2d104ec58a')"

# Cleanup
rm -f file

echo ""
echo "Results: $PASS passed, $FAIL failed"
