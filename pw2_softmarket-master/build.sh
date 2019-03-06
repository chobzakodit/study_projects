#!/bin/sh
cd ./front
npm i
npm audit fix
npm run build
npm install components
cp -r ./build/static ../public/
cp -r ./build/index.html ../public/
