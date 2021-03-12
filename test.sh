#! bash -uvx
bash -l -c "echo `cygpath -w ~/ | sed -e 's \\\\ / g'`"