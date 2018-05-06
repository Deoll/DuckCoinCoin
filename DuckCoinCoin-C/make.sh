#! /bin/sh

if [ $# -ne 1 ]
then
	echo "Usage: $0 number"
	exit 1
fi
if [ $1 -eq 1 ]
then
	gcc Transaction.c sha256.c sha256.h Transaction.h sha256_utils.h sha256_utils.c -o trans
fi

if [ $1 -eq 2 ]
then
	gcc Transaction.c sha256.c sha256.h Transaction.h sha256_utils.h sha256_utils.c block.c block.h -o block
fi

if [ $1 -eq 3 ]
then
	gcc Transaction.c sha256.c sha256.h blockchain.c blockchain.h Transaction.h sha256_utils.h sha256_utils.c block.c block.h -o blockchain
fi
exit 0
