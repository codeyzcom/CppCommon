//
// Created by user on 1/18/21.
//

#include <fstream>

class FileHandle {
public:
    FileHandle(const char *name, const char *mode) {
        f_ = fopen(name, mode);
    }

    ~FileHandle() {
        if (f_ != nullptr) {
            fclose(f_);
        }
    }

    FILE *file() {
        return f_;
    }

private:
    FILE *f_;
};