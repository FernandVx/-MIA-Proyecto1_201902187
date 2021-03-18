#!/bin/sh -
sed -i 's/=\([a-zA-Z0-9/\.]\+\)/="\1"/g' /tmp/parte*
