#!/usr/bin/env python3

################################################################################

import sys
import math
import numpy

################################################################################

MPH_2_MPS = 0.44704
FT_2_M = 0.3048

################################################################################

def get_n(v,d,j):
    n = v / (j*d)
    return n

################################################################################

def print_cols(args,cols):
    for ir in range(0,len(args),1):
        out = str(args[ir])
        for ic in range(0,len(cols),1):
            out += ";"
            value = cols[ic][ir]
            if value != None:
                out += str(round(value,6))
        print(out)

################################################################################

def print_rows(args,rows):
    for i in range(0,len(args),1):
        out = str(args[i])
        row = rows[i]
        for value in row:
            out += ";"
            if value != None:
                out += str(round(value,6))
        print(out)

################################################################################

class DataInput(object):
    
    def __init__(self,v,d):
        self.v = v
        self.d = d
        self.args = []
        self.rows = []
        self.cols = []
        self.rows_no = 0
        self.cols_no = 0
    
    
    
    def read_file(self,in_file):
        data_file = open(in_file,"r")
        lines = data_file.readlines()
        data_file.close()
        lines = lines[2:]
        for line in lines:
            values = line.split(";")
            self.args.append(float(values[0]))
            values_rest = values[1:]
            row = []
            for value in values_rest:
                if len(value) > 0 and value != "\n":
                    row.append(float(value))
                else:
                    row.append(None)
            self.rows.append(row)
        self.rows_no = len(self.rows)
        self.rows_2_cols()
    
    
    
    def rows_2_cols(self):
        if len(self.rows) > 0:
            row = self.rows[0]
            self.cols_no = len(row)
        for ic in range(0,self.cols_no,1):
            col = []
            self.cols.append(col)
        for ic in range(0,len(self.cols),1):
            for ir in range(0,len(self.rows),1):
                self.cols[ic].append(self.rows[ir][ic])
    
    
    
    def ndv_2_j(self):
        result = []
        for arg in self.args:
            j = 1.0 / arg
            result.append( j )
        return result
    
    
    
    def qc_2_cp(self):
        cols_new = []
        for ic in range(0,len(self.cols),1):
            col = []
            cols_new.append(col)
        for ic in range(0,len(self.cols),1):
            cp = 0.0
            for ir in range(0,len(self.args),1):
                j = 1.0 / self.args[ir]
                n = get_n(self.v,self.d,j)
                qc = self.cols[ic][ir]
                if qc != None:
                    cp = 2.0 * math.pi * (self.v**2) * qc / ( (n**2) * (self.d**2) )
                cols_new[ic].append(cp)
        return cols_new
    
    
    
    def tc_2_ct(self):
        cols_new = []
        for ic in range(0,len(self.cols),1):
            col = []
            cols_new.append(col)
        for ic in range(0,len(self.cols),1):
            ct = 0.0
            for ir in range(0,len(self.args),1):
                j = 1.0 / self.args[ir]
                n = get_n(self.v,self.d,j)
                tc = self.cols[ic][ir]
                if tc != None:
                    ct = (self.v**2) * tc / ( (n**2) * (self.d**2) )
                cols_new[ic].append(ct)
        return cols_new

################################################################################

class DataOutput(object):
    
    def __init__(self,v,d):
        self.v = v
        self.d = d
        self.args = []
        self.cols = []
        self.rows_no = 0
        self.cols_no = 0
    
    
    
    def init_args(self,start,stop,step):
        arg = start
        while ( arg < stop ):
            self.args.append( arg )
            arg += step
            arg = round( arg, 2 )
        self.rows_no = len(self.args)
    
    
    
    def init_cols(self,args,cols):
        self.cols_no = len(cols)
        for ic in range(0,self.cols_no,1):
            col = []
            self.cols.append(col)
        for ic in range(0,self.cols_no,1):
            self.cols[ic] = numpy.interp(self.args,args,cols[ic])
    
    
    
    def write_file(self,out_file):
        data_file = open(out_file,"w")
        for ir in range(0,len(self.args),1):
            out = str(self.args[ir])
            for ic in range(0,len(self.cols),1):
                out += ";"
                value = self.cols[ic][ir]
                if value != None:
                    out += str(round(value,6))
            out += "\n"
            data_file.write(out)
        data_file.close()


################################################################################

def process(qc_in_file,tc_in_file,cp_out_file,ct_out_file):
    v = MPH_2_MPS*105.0
    d = FT_2_M*10.0
        
    data_in_qc = DataInput(v,d)
    data_in_tc = DataInput(v,d)
    
    data_in_qc.read_file(qc_in_file)
    data_in_tc.read_file(tc_in_file)

    args_cp = data_in_qc.ndv_2_j()
    cols_cp = data_in_qc.qc_2_cp()
    
    args_ct = data_in_tc.ndv_2_j()
    cols_ct = data_in_tc.tc_2_ct()
    
    args_cp.reverse()
    args_ct.reverse()
    
    for col in cols_cp:
        col.reverse()
    
    for col in cols_ct:
        col.reverse()
    
    data_out_cp = DataOutput(v,d)
    data_out_ct = DataOutput(v,d)
    
    data_out_cp.init_args(0.1,5.0+1e-9,0.1)
    data_out_ct.init_args(0.1,5.0+1e-9,0.1)
    
    data_out_cp.init_cols(args_cp,cols_cp)
    data_out_ct.init_cols(args_ct,cols_ct)
    
    data_out_cp.write_file(cp_out_file)
    data_out_ct.write_file(ct_out_file)

################################################################################

if len(sys.argv) == 5:
    qc_in_file = sys.argv[1]
    tc_in_file = sys.argv[2]
    cp_out_file = sys.argv[3]
    ct_out_file = sys.argv[4]
    process(qc_in_file,tc_in_file,cp_out_file,ct_out_file)
else:
    print("Usage:")
    print("convert.py qc_input_file tc_input_file cp_output_file ct_output_file")
