//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
`timescale 1 ns / 100 ps

module system_tb;

//----------------------------------------------------------------------------
// Parameter (may differ for physical synthesis)
//----------------------------------------------------------------------------
parameter tck              = 10;       // clock period in ns
parameter uart_baud_rate   = 1152000;  // uart baud rate for simulation 

parameter clk_freq = 1000000000 / tck; // Frequenzy in HZ
//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
reg        clk;
reg        rst;
reg [7:0]  gpio;
wire [7:0] Q;
wire       led;
wire       led5;

//----------------------------------------------------------------------------
// UART STUFF (testbench uart, simulating a comm. partner)
//----------------------------------------------------------------------------
wire         uart_rxd;
wire         uart_txd;


//----------------------------------------------------------------------------
// Device Under Test 
//----------------------------------------------------------------------------
system #(
	.clk_freq(           clk_freq         ),
	.uart_baud_rate(     uart_baud_rate   )
) dut  (
	.clk(          clk    ),
	// Debug
	.rst(          rst    ),
	.led(          led    ),
	// Uart
	.uart_rxd(  uart_rxd  ),
	.uart_txd(  uart_txd  ),
        .gpio_io( Q)
     
);

/* Clocking device */
initial         clk <= 0;
always #(tck/2) clk <= ~clk;
assign Q = gpio;
/* Simulation setup */
initial begin



	$dumpfile("system_tb.vcd");
	//$monitor("%b,%b,%b,%b",clk,rst,uart_txd,uart_rxd);
	$dumpvars(-1, dut);
	//$dumpvars(-1,clk,rst,uart_txd);
	// reset
       
	#0  rst <= 0;
	#80 rst <= 1;
        gpio <=8'h00;
        #1000000 gpio<= 8'h01;
        #100000 gpio<= 8'h00;
        #100000 gpio<= 8'h01;
        #200000 gpio<= 8'h00;
        #100000 gpio<= 8'h01;
        #100000 gpio<= 8'h00;
        #100000 gpio<= 8'h01;
        #200000 gpio<= 8'h00;
        #100000 gpio<= 8'h01;
        #100000 gpio<= 8'h00;
	#(tck*20000) $finish;
end



endmodule
