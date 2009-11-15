#include "python_script.h"
#include <stdio.h>
#include <GsTLAppli/utils/gstl_messages.h>

#ifdef _DEBUG
#undef _DEBUG
#include <Python.h>
#define _DEBUG
#else
#include <Python.h>
#endif

Named_interface* Python_script::create_new_interface(std::string& _filename) {
	return new Python_script(_filename);
}

Python_script::Python_script(const std::string& _filename) :
	filename_(_filename) {
}

Python_script::~Python_script() {
}

std::string Python_script::filename() const {
	return filename_;
}

void Python_script::execute() const {

	PyRun_SimpleString(""
		"import redirect\n"
		"class CoutLogger:\n"
		"    def __init__(self):\n"
		"        self.buf = []\n"
		"    def write(self, data):\n"
		"        self.buf.append(data)\n"
		"        if data.endswith('\\n'):\n"
		"            redirect.sgems_cout(''.join(self.buf))\n"
		"            self.buf = []\n"
		"\n"
		"class CerrLogger:\n"
		"    def __init__(self):\n"
		"        self.buf = []\n"
		"    def write(self, data):\n"
		"        self.buf.append(data)\n"
		"        if data.endswith('\\n'):\n"
		"            redirect.sgems_cerr(''.join(self.buf))\n"
		"            self.buf = []\n"
		"\n"
		"import sys\n"
		"sys.stdout = CoutLogger()\n"
		"sys.stderr = CerrLogger()\n"
		"");

	FILE* fp = fopen(filename_.c_str(), "r");
	if (!fp) {
		GsTLcerr << "can't open file " << filename_ << gstlIO::end;
		return;
	}

	PyRun_SimpleFile(fp, filename_.c_str());
	fclose(fp);
}
