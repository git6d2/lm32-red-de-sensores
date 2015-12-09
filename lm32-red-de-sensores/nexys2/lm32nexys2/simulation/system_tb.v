//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
`timescale 1 ns / 100 ps


module system_tb;

//----------------------------------------------------------------------------
// Parameter (may differ for physical synthesis)
//----------------------------------------------------------------------------
parameter tck              = 20;       // clock period in ns
parameter uart_baud_rate   = 1152000;  // uart baud rate for simulation 

parameter clk_freq = 1000000000 / tck; // Frequenzy in HZ
//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
reg        clk;
reg        rst;
wire       led;

//----------------------------------------------------------------------------
// UART STUFF (testbench uart, simulating a comm. partner)
//----------------------------------------------------------------------------
wire         uart_rxd;
wire         uart_txd;

//------------------------------------------------------------------------------
// SPI
//------------------------------------------------------------------------------
wire 	     spi_miso;
wire	     spi_mosi;
wire 	     spi_clk;
wire [3:0]   spi_cs;

//------------------------------------------------------------------------------
// GPIO
//------------------------------------------------------------------------------
wire [7:0]   gpio_io;


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
	//Spi
	//.spi_miso(  spi_miso  ),
	//.spi_mosi(  spi_mosi  ),
	//.spi_clk(  spi_clk  ),
	//.spi_cs(  spi_cs  ),
	// Uart
	.uart_rxd(  uart_rxd  ),
	.uart_txd(  uart_txd  )
);

/* Clocking device */
initial         clk <= 0;
always #(tck/2) clk <= ~clk;

/* Simulation setup */
initial begin



	$dumpfile("system_tb.vcd");
	//$monitor("%b,%b,%b,%b",clk,rst,uart_txd,uart_rxd);
	$dumpvars(-1, dut);
	//$dumpvars(-1,clk,rst,uart_txd,spi_miso,spi_cs,spi_clk);
	// reset
	#0  rst <= 0;
	#80 rst <= 1;

	#(tck*2000000) $finish;
end



endmodule
