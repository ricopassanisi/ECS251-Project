# ECS251-Project
UC Davis ECS 251 Operating Systems Project


## For rvconsole.sh

Replace **lines 51 & 52** with:

```sh
echo "  docker run -it -v $(pwd):/code -v "$(dirname $(pwd))/cartridge":/code/workspace/cartridge -v "$(dirname $(pwd))/firmware":/code/workspace/firmware ${RUN_ARGS[@]}"
        docker run -it -v "$(pwd)":/code -v "$(dirname $(pwd))/cartridge":/code/workspace/cartridge -v "$(dirname $(pwd))/firmware":/code/workspace/firmware "${RUN_ARGS[@]}"
```
