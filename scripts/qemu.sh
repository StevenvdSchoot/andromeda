#!/bin/bash
export KERN_PATH=bin/andromeda.img
export MEM_SIZE="64M"
export HDA_TYPE=""
export HDA_IMAGE="hda.img"
export HDA_IMAGE_QCOW="hda.qcow"

export QEMU_FLAGS="-kernel $KERN_PATH -m $MEM_SIZE -monitor stdio"

if [ "$HDA_TYPE" = "qcow" ]; then
	if [ ! -f $HDA_IMAGE_QCOW ]; then
		qemu-img create -f qcow $HDA_IMAGE_QCOW 750M
	fi
	export QEMU_FLAGS="$QEMU_FLAGS -hda $HDA_IMAGE_QCOW"
else
	if [ ! -f $HDA_IMAGE ]; then
		dd if=/dev/zero of=$HDA_IMAGE count=1M
	fi
	export QEMU_FLAGS="$QEMU_FLAGS -hda $HDA_IMAGE"
fi

echo $QEMU_FLAGS

if ! command -v qemu-kvm; then
	if ! command -v qemu-system-i386; then
		qemu $QEMU_FLAGS
	else
		qemu-system-i386 $QEMU_FLAGS
	fi;
else
	qemu-kvm $QEMU_FLAGS
fi
