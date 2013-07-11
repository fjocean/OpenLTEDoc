My Main Page                         {#mainpage}
============

The directory structure for the project is:

* **octave**              Octave test code
* **cmn_hdr**               Common header files
* **liblte**                C++ library of commonly used LTE functions
* **cmake**                 Files needed for cmake
* **build**                 Cmake generated build files
* **LTE_fdd_dl_file_scan**  A gnu-radio LTE FDD DL file scanner application
* **LTE_fdd_dl_file_gen**   A gnu-radio LTE FDD DL file generator application
* **LTE_fdd_dl_scan**       A gnu-radio LTE FDD DL scanner application that currently supports rtl-sdr hardware

### FDD DL file generator:
* The GNU Radio flow graph: LTE_fdd_dl_file_gen
* The main GNU Radio block: LTE_fdd_dl_fg_samp_buf
* The main loop: LTE_fdd_dl_fg_samp_buf::work

### FDD DL file scanner:
* The GNU Radio flow graph: LTE_fdd_dl_file_scan
* The main GNU Radio block: LTE_fdd_dl_fs_samp_buf
* The main loop: LTE_fdd_dl_fs_samp_buf::work

### FDD DL scanner :
* The GNU Radio flow graph: LTE_fdd_dl_scan_flowgraph
* The main GNU Radio block: LTE_fdd_dl_scan_state_machine
* The main loop: LTE_fdd_dl_scan_state_machine::work
