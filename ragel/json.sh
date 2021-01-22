#! bash -uvx
ragel -Z json.rl
ls -ltr json.go
ragel -Vp json.rl > json.dot
dot -Tpng json.dot > json.png
ls -ltr json.png
