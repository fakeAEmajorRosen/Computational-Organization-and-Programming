#!/bin/bash

imageName="gtcs2110/hw05-fall20"

docker -v >/dev/null

dockerExists=$?

if [ $dockerExists != 0 ]; then
  >&2 echo "ERROR: Please install Docker before running this script. Refer to the CS 2110 Docker Guide."
  exit 1
fi

docker container ls >/dev/null
dockerNotRunning=$?

if [ $dockerNotRunning != 0 ]; then
  >&2 echo "ERROR: Docker is not currently running. Please start Docker before running this script."
  exit 1
fi

echo "Attempting to pull down most recent image of $imageName..."
docker pull "$imageName"

successfulPull=$?

if [ $successfulPull != 0 ]; then
  >&2 echo "WARNING: Unable to pull down the most recent image of $imageName"
fi

docker run --rm -i -v "$(pwd)":/autograder/submission/ "$imageName" /bin/sh -c "/autograder/run_local"
