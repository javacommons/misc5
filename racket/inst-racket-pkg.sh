#! bash -uvx
raco pkg install --auto racket-langserver
raco pkg install --auto gregor-lib
raco pkg install --auto http
raco pkg install --auto msgpack
raco pkg install --auto mred-designer
# racket -l mred-designer
#;https://docs.racket-lang.org/dyoo-while-loop/index.html
#;(require dyoo-while-loop) ; raco pkg install --auto while-loop
raco pkg install --auto while-loop
