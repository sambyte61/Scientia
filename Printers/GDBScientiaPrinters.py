
import sys
import gdb

sys.path.append("/usr/share/gcc/python")  # This is often already added by GDB
import libstdcxx.v6.printers as libstdcxxpp

# Use the base class if available.
if hasattr(gdb, 'ValuePrinter'):
    printer_base = gdb.ValuePrinter
else:
    printer_base = object

if sys.version_info[0] == 3:
    Iterator = object
else:
    class Iterator(object):

        def next(self):
            return type(self).__next__(self)

def default_iterator(val):
    for field in val.type.fields():
        yield field.name, val[field.name]

class TMatrixPrinter:
    """Pretty Printer for TMatrix<T>"""

    def __init__(self, val):
        self.val = val
        self.rows = int(val['Rows'])
        self.cols = int(val['Cols'])
        self.t_type = val.type.template_argument(0)

    def to_string(self):
        tparam = self.val.type.template_argument(0)
        return f"TMatrix<{tparam}> [{self.rows}x{self.cols}]"

    def display_hint(self):
        return 'array'

    def get_matrix_value(self, i, j):
        row_tuple = self.val['Data']['_M_t']['_M_t']

        row_ptr = libstdcxxpp.tuple_get(0, row_tuple)

        tparam = self.val.type.template_argument(0)  # This is T (like int)
        row_unique_ptr_type = gdb.lookup_type(f'std::unique_ptr<{tparam.name} [], std::default_delete<{tparam.name} []>>')

        row_unique_ptr = (row_ptr + i).dereference().cast(row_unique_ptr_type)

        row_data_ptr = libstdcxxpp.unique_ptr_get(row_unique_ptr)

        # Return j-th element
        return (row_data_ptr + j).dereference()


    def children(self):
        yield ('Rows', self.val['Rows'])
        yield ('Cols', self.val['Cols'])

        for i in range(self.rows):
            for j in range(self.cols):
                try:
                    val = self.get_matrix_value(i, j)
                    if val is not None:
                        yield (f"[{i}][{j}]", val)
                except Exception:
                    print(Exception)

def build_scientia_pretty_printer():
    pp = gdb.printing.RegexpCollectionPrettyPrinter("scientia")
    pp.add_printer("TMatrix", "^TMatrix<.*>$", TMatrixPrinter)
    return pp

def register_scientia_printers(objfile):
    if objfile == None:
        objfile = gdb.current_objfile()
    gdb.printing.register_pretty_printer(objfile, build_scientia_pretty_printer(), True)
    print("Registered pretty printers for Scientia classes")

register_scientia_printers(None)