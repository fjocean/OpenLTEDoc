/*******************************************************************************

    Copyright 2013 Ben Wojtowicz

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*******************************************************************************

    File: LTE_fdd_dl_scan_interface.h

    Description: Contains all the definitions for the LTE FDD DL Scanner
                 interface.

    Revision History
    ----------    -------------    --------------------------------------------
    02/26/2013    Ben Wojtowicz    Created file

*******************************************************************************/

#ifndef __LTE_FDD_DL_SCAN_INTERFACE_H__
#define __LTE_FDD_DL_SCAN_INTERFACE_H__

/*******************************************************************************
                              INCLUDES
*******************************************************************************/

#include "liblte_interface.h"
#include "liblte_rrc.h"
#include "libtools_socket_wrap.h"
#include <boost/thread/mutex.hpp>
#include <string>

/*******************************************************************************
                              DEFINES
*******************************************************************************/

#define LTE_FDD_DL_SCAN_DEFAULT_CTRL_PORT 20000

/*******************************************************************************
                              FORWARD DECLARATIONS
*******************************************************************************/


/*******************************************************************************
                              TYPEDEFS
*******************************************************************************/

typedef enum{
    LTE_FDD_DL_SCAN_STATUS_OK = 0,
    LTE_FDD_DL_SCAN_STATUS_FAIL,
}LTE_FDD_DL_SCAN_STATUS_ENUM;

typedef struct{
    LIBLTE_RRC_MIB_STRUCT                   mib;
    LIBLTE_RRC_SYS_INFO_BLOCK_TYPE_1_STRUCT sib1;
    LIBLTE_RRC_SYS_INFO_BLOCK_TYPE_2_STRUCT sib2;
    LIBLTE_RRC_SYS_INFO_BLOCK_TYPE_3_STRUCT sib3;
    LIBLTE_RRC_SYS_INFO_BLOCK_TYPE_4_STRUCT sib4;
    LIBLTE_RRC_SYS_INFO_BLOCK_TYPE_5_STRUCT sib5;
    LIBLTE_RRC_SYS_INFO_BLOCK_TYPE_6_STRUCT sib6;
    LIBLTE_RRC_SYS_INFO_BLOCK_TYPE_7_STRUCT sib7;
    LIBLTE_RRC_SYS_INFO_BLOCK_TYPE_8_STRUCT sib8;
    float                                   freq_offset;
    uint32                                  N_id_cell;
    uint32                                  sfn;
    uint8                                   N_ant;
    bool                                    sib1_present;
    bool                                    sib2_present;
    bool                                    sib3_present;
    bool                                    sib4_present;
    bool                                    sib5_present;
    bool                                    sib6_present;
    bool                                    sib7_present;
    bool                                    sib8_present;
}LTE_FDD_DL_SCAN_CHAN_DATA_STRUCT;

/*******************************************************************************
                              CLASS DECLARATIONS
*******************************************************************************/

class LTE_fdd_dl_scan_interface
{
public:
    // Singleton
    static LTE_fdd_dl_scan_interface* get_instance(void);
    static void cleanup(void);

    // Communication
    void set_ctrl_port(int16 port);
    void start_ctrl_port(void);
    void stop_ctrl_port(void);
    void send_ctrl_msg(std::string msg);
    void send_ctrl_info_msg(std::string msg);
    void send_ctrl_channel_found_msg(LTE_FDD_DL_SCAN_CHAN_DATA_STRUCT *chan_data);
    void send_ctrl_channel_not_found_msg(void);
    void send_ctrl_status_msg(LTE_FDD_DL_SCAN_STATUS_ENUM status, std::string msg);
    static void handle_ctrl_msg(std::string msg);
    static void handle_ctrl_connect(void);
    static void handle_ctrl_disconnect(void);
    static void handle_ctrl_error(LIBTOOLS_SOCKET_WRAP_ERROR_ENUM err);
    boost::mutex          ctrl_mutex;
    libtools_socket_wrap *ctrl_socket;
    int16                 ctrl_port;
    static bool           ctrl_connected;

    // Get/Set
    bool get_shutdown(void);

    // Helpers
    LTE_FDD_DL_SCAN_STATUS_ENUM switch_to_next_freq(void);

private:
    // Singleton
    static LTE_fdd_dl_scan_interface *instance;
    LTE_fdd_dl_scan_interface();
    ~LTE_fdd_dl_scan_interface();

    // Handlers
    void handle_read(std::string msg);
    void handle_write(std::string msg);
    void handle_start(void);
    void handle_stop(void);
    void handle_help(void);

    // Reads/Writes
    void read_band(void);
    void write_band(std::string band_str);
    void read_dl_earfcn_list(void);
    void write_dl_earfcn_list(std::string dl_earfcn_list_str);
    void read_repeat(void);
    void write_repeat(std::string repeat_str);

    // Variables
    boost::mutex               dl_earfcn_list_mutex;
    LIBLTE_INTERFACE_BAND_ENUM band;
    uint16                     current_dl_earfcn;
    uint16                     dl_earfcn_list[65535];
    uint16                     dl_earfcn_list_size;
    uint16                     dl_earfcn_list_idx;
    bool                       repeat;
    bool                       shutdown;
};

#endif /* __LTE_FDD_DL_SCAN_INTERFACE_H__ */
