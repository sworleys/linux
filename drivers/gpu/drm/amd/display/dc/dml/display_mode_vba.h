/*
 * Copyright 2017 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: AMD
 *
 */


#ifndef __DML2_DISPLAY_MODE_VBA_H__
#define __DML2_DISPLAY_MODE_VBA_H__

#include "dml_common_defs.h"

struct display_mode_lib;

void ModeSupportAndSystemConfiguration(struct display_mode_lib *mode_lib);

#define dml_get_attr_decl(attr) double get_##attr(struct display_mode_lib *mode_lib, const display_e2e_pipe_params_st *pipes, unsigned int num_pipes)

dml_get_attr_decl(clk_dcf_deepsleep);
dml_get_attr_decl(wm_urgent);
dml_get_attr_decl(wm_memory_trip);
dml_get_attr_decl(wm_writeback_urgent);
dml_get_attr_decl(wm_stutter_exit);
dml_get_attr_decl(wm_stutter_enter_exit);
dml_get_attr_decl(wm_dram_clock_change);
dml_get_attr_decl(wm_writeback_dram_clock_change);
dml_get_attr_decl(wm_xfc_underflow);
dml_get_attr_decl(stutter_efficiency_no_vblank);
dml_get_attr_decl(stutter_efficiency);
dml_get_attr_decl(urgent_latency);
dml_get_attr_decl(urgent_extra_latency);
dml_get_attr_decl(nonurgent_latency);
dml_get_attr_decl(dram_clock_change_latency);
dml_get_attr_decl(dispclk_calculated);
dml_get_attr_decl(total_data_read_bw);
dml_get_attr_decl(return_bw);
dml_get_attr_decl(tcalc);
dml_get_attr_decl(fraction_of_urgent_bandwidth);
dml_get_attr_decl(fraction_of_urgent_bandwidth_imm_flip);

#define dml_get_pipe_attr_decl(attr) double get_##attr(struct display_mode_lib *mode_lib, const display_e2e_pipe_params_st *pipes, unsigned int num_pipes, unsigned int which_pipe)

dml_get_pipe_attr_decl(dsc_delay);
dml_get_pipe_attr_decl(dppclk_calculated);
dml_get_pipe_attr_decl(dscclk_calculated);
dml_get_pipe_attr_decl(min_ttu_vblank);
dml_get_pipe_attr_decl(vratio_prefetch_l);
dml_get_pipe_attr_decl(vratio_prefetch_c);
dml_get_pipe_attr_decl(dst_x_after_scaler);
dml_get_pipe_attr_decl(dst_y_after_scaler);
dml_get_pipe_attr_decl(dst_y_per_vm_vblank);
dml_get_pipe_attr_decl(dst_y_per_row_vblank);
dml_get_pipe_attr_decl(dst_y_prefetch);
dml_get_pipe_attr_decl(dst_y_per_vm_flip);
dml_get_pipe_attr_decl(dst_y_per_row_flip);
dml_get_pipe_attr_decl(xfc_transfer_delay);
dml_get_pipe_attr_decl(xfc_precharge_delay);
dml_get_pipe_attr_decl(xfc_remote_surface_flip_latency);
dml_get_pipe_attr_decl(xfc_prefetch_margin);
dml_get_pipe_attr_decl(refcyc_per_vm_group_vblank);
dml_get_pipe_attr_decl(refcyc_per_vm_group_flip);
dml_get_pipe_attr_decl(refcyc_per_vm_req_vblank);
dml_get_pipe_attr_decl(refcyc_per_vm_req_flip);

unsigned int get_vstartup_calculated(
		struct display_mode_lib *mode_lib,
		const display_e2e_pipe_params_st *pipes,
		unsigned int num_pipes,
		unsigned int which_pipe);

double get_total_immediate_flip_bytes(
		struct display_mode_lib *mode_lib,
		const display_e2e_pipe_params_st *pipes,
		unsigned int num_pipes);
double get_total_immediate_flip_bw(
		struct display_mode_lib *mode_lib,
		const display_e2e_pipe_params_st *pipes,
		unsigned int num_pipes);
double get_total_prefetch_bw(
		struct display_mode_lib *mode_lib,
		const display_e2e_pipe_params_st *pipes,
		unsigned int num_pipes);
unsigned int dml_get_voltage_level(
		struct display_mode_lib *mode_lib,
		const display_e2e_pipe_params_st *pipes,
		unsigned int num_pipes);

void PixelClockAdjustmentForProgressiveToInterlaceUnit(struct display_mode_lib *mode_lib);

bool Calculate256BBlockSizes(
		enum source_format_class SourcePixelFormat,
		enum dm_swizzle_mode SurfaceTiling,
		unsigned int BytePerPixelY,
		unsigned int BytePerPixelC,
		unsigned int *BlockHeight256BytesY,
		unsigned int *BlockHeight256BytesC,
		unsigned int *BlockWidth256BytesY,
		unsigned int *BlockWidth256BytesC);

struct vba_vars_st {
	ip_params_st ip;
	soc_bounding_box_st soc;

	int maxMpcComb;
	bool UseMaximumVStartup;

	double WritebackDISPCLK;
	double DPPCLKUsingSingleDPPLuma;
	double DPPCLKUsingSingleDPPChroma;
	double DISPCLKWithRamping;
	double DISPCLKWithoutRamping;
	double GlobalDPPCLK;
	double DISPCLKWithRampingRoundedToDFSGranularity;
	double DISPCLKWithoutRampingRoundedToDFSGranularity;
	double MaxDispclkRoundedToDFSGranularity;
	bool DCCEnabledAnyPlane;
	double ReturnBandwidthToDCN;
	unsigned int TotalActiveDPP;
	unsigned int TotalDCCActiveDPP;
	double UrgentRoundTripAndOutOfOrderLatency;
	double StutterPeriod;
	double FrameTimeForMinFullDETBufferingTime;
	double AverageReadBandwidth;
	double TotalRowReadBandwidth;
	double PartOfBurstThatFitsInROB;
	double StutterBurstTime;
	unsigned int NextPrefetchMode;
	double NextMaxVStartup;
	double VBlankTime;
	double SmallestVBlank;
	double DCFCLKDeepSleepPerPlane[DC__NUM_DPP__MAX];
	double EffectiveDETPlusLBLinesLuma;
	double EffectiveDETPlusLBLinesChroma;
	double UrgentLatencySupportUsLuma;
	double UrgentLatencySupportUsChroma;
	unsigned int DSCFormatFactor;

	bool DummyPStateCheck;
	bool DRAMClockChangeSupportsVActive;
	bool PrefetchModeSupported;
	bool PrefetchAndImmediateFlipSupported;
	enum self_refresh_affinity AllowDRAMSelfRefreshOrDRAMClockChangeInVblank; // Mode Support only
	double XFCRemoteSurfaceFlipDelay;
	double TInitXFill;
	double TslvChk;
	double SrcActiveDrainRate;
	bool ImmediateFlipSupported;
	enum mpc_combine_affinity WhenToDoMPCCombine; // Mode Support only

	bool PrefetchERROR;

	unsigned int VStartupLines;
	unsigned int ActiveDPPs;
	unsigned int LBLatencyHidingSourceLinesY;
	unsigned int LBLatencyHidingSourceLinesC;
	double ActiveDRAMClockChangeLatencyMargin[DC__NUM_DPP__MAX];
	double MinActiveDRAMClockChangeMargin;
	double InitFillLevel;
	double FinalFillMargin;
	double FinalFillLevel;
	double RemainingFillLevel;
	double TFinalxFill;

	//
	// SOC Bounding Box Parameters
	//
	double SRExitTime;
	double SREnterPlusExitTime;
	double UrgentLatencyPixelDataOnly;
	double UrgentLatencyPixelMixedWithVMData;
	double UrgentLatencyVMDataOnly;
	double UrgentLatency; // max of the above three
	double WritebackLatency;
	double PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyPixelDataOnly; // Mode Support
	double PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyPixelMixedWithVMData; // Mode Support
	double PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyVMDataOnly; // Mode Support
	double MaxAveragePercentOfIdealSDPPortBWDisplayCanUseInNormalSystemOperation; // Mode Support
	double MaxAveragePercentOfIdealDRAMBWDisplayCanUseInNormalSystemOperation; // Mode Support
	double NumberOfChannels;
	double DRAMChannelWidth;
	double FabricDatapathToDCNDataReturn;
	double ReturnBusWidth;
	double Downspreading;
	double DISPCLKDPPCLKDSCCLKDownSpreading;
	double DISPCLKDPPCLKVCOSpeed;
	double RoundTripPingLatencyCycles;
	double UrgentOutOfOrderReturnPerChannel;
	double UrgentOutOfOrderReturnPerChannelPixelDataOnly;
	double UrgentOutOfOrderReturnPerChannelPixelMixedWithVMData;
	double UrgentOutOfOrderReturnPerChannelVMDataOnly;
	unsigned int VMMPageSize;
	double DRAMClockChangeLatency;
	double XFCBusTransportTime;
	bool UseUrgentBurstBandwidth;
	double XFCXBUFLatencyTolerance;

	//
	// IP Parameters
	//
	unsigned int ROBBufferSizeInKByte;
	double DETBufferSizeInKByte;
	double DETBufferSizeInTime;
	unsigned int DPPOutputBufferPixels;
	unsigned int OPPOutputBufferLines;
	unsigned int PixelChunkSizeInKByte;
	double ReturnBW;
	bool GPUVMEnable;
	bool HostVMEnable;
	unsigned int GPUVMMaxPageTableLevels;
	unsigned int HostVMMaxPageTableLevels;
	unsigned int HostVMCachedPageTableLevels;
	unsigned int OverrideGPUVMPageTableLevels;
	unsigned int OverrideHostVMPageTableLevels;
	unsigned int MetaChunkSize;
	double MinPixelChunkSizeBytes;
	double MinMetaChunkSizeBytes;
	unsigned int WritebackChunkSize;
	bool ODMCapability;
	unsigned int NumberOfDSC;
	unsigned int LineBufferSize;
	unsigned int MaxLineBufferLines;
	unsigned int WritebackInterfaceLumaBufferSize;
	unsigned int WritebackInterfaceChromaBufferSize;
	unsigned int WritebackChromaLineBufferWidth;
	enum writeback_config WritebackConfiguration;
	double MaxDCHUBToPSCLThroughput;
	double MaxPSCLToLBThroughput;
	unsigned int PTEBufferSizeInRequestsLuma;
	unsigned int PTEBufferSizeInRequestsChroma;
	double DISPCLKRampingMargin;
	unsigned int MaxInterDCNTileRepeaters;
	bool XFCSupported;
	double XFCSlvChunkSize;
	double XFCFillBWOverhead;
	double XFCFillConstant;
	double XFCTSlvVupdateOffset;
	double XFCTSlvVupdateWidth;
	double XFCTSlvVreadyOffset;
	double DPPCLKDelaySubtotal;
	double DPPCLKDelaySCL;
	double DPPCLKDelaySCLLBOnly;
	double DPPCLKDelayCNVCFormater;
	double DPPCLKDelayCNVCCursor;
	double DISPCLKDelaySubtotal;
	bool ProgressiveToInterlaceUnitInOPP;
	// Pipe/Plane Parameters
	int VoltageLevel;
	double FabricClock;
	double DRAMSpeed;
	double DISPCLK;
	double SOCCLK;
	double DCFCLK;

	unsigned int NumberOfActivePlanes;
	unsigned int NumberOfDSCSlices[DC__NUM_DPP__MAX];
	unsigned int ViewportWidth[DC__NUM_DPP__MAX];
	unsigned int ViewportHeight[DC__NUM_DPP__MAX];
	unsigned int ViewportYStartY[DC__NUM_DPP__MAX];
	unsigned int ViewportYStartC[DC__NUM_DPP__MAX];
	unsigned int PitchY[DC__NUM_DPP__MAX];
	unsigned int PitchC[DC__NUM_DPP__MAX];
	double HRatio[DC__NUM_DPP__MAX];
	double VRatio[DC__NUM_DPP__MAX];
	unsigned int htaps[DC__NUM_DPP__MAX];
	unsigned int vtaps[DC__NUM_DPP__MAX];
	unsigned int HTAPsChroma[DC__NUM_DPP__MAX];
	unsigned int VTAPsChroma[DC__NUM_DPP__MAX];
	unsigned int HTotal[DC__NUM_DPP__MAX];
	unsigned int VTotal[DC__NUM_DPP__MAX];
	unsigned int VTotal_Max[DC__NUM_DPP__MAX];
	unsigned int VTotal_Min[DC__NUM_DPP__MAX];
	int DPPPerPlane[DC__NUM_DPP__MAX];
	double PixelClock[DC__NUM_DPP__MAX];
	double PixelClockBackEnd[DC__NUM_DPP__MAX];
	bool DCCEnable[DC__NUM_DPP__MAX];
	bool FECEnable[DC__NUM_DPP__MAX];
	unsigned int DCCMetaPitchY[DC__NUM_DPP__MAX];
	unsigned int DCCMetaPitchC[DC__NUM_DPP__MAX];
	enum scan_direction_class SourceScan[DC__NUM_DPP__MAX];
	enum source_format_class SourcePixelFormat[DC__NUM_DPP__MAX];
	bool WritebackEnable[DC__NUM_DPP__MAX];
	unsigned int ActiveWritebacksPerPlane[DC__NUM_DPP__MAX];
	double WritebackDestinationWidth[DC__NUM_DPP__MAX];
	double WritebackDestinationHeight[DC__NUM_DPP__MAX];
	double WritebackSourceHeight[DC__NUM_DPP__MAX];
	enum source_format_class WritebackPixelFormat[DC__NUM_DPP__MAX];
	unsigned int WritebackLumaHTaps[DC__NUM_DPP__MAX];
	unsigned int WritebackLumaVTaps[DC__NUM_DPP__MAX];
	unsigned int WritebackChromaHTaps[DC__NUM_DPP__MAX];
	unsigned int WritebackChromaVTaps[DC__NUM_DPP__MAX];
	double WritebackHRatio[DC__NUM_DPP__MAX];
	double WritebackVRatio[DC__NUM_DPP__MAX];
	unsigned int HActive[DC__NUM_DPP__MAX];
	unsigned int VActive[DC__NUM_DPP__MAX];
	bool Interlace[DC__NUM_DPP__MAX];
	enum dm_swizzle_mode SurfaceTiling[DC__NUM_DPP__MAX];
	unsigned int ScalerRecoutWidth[DC__NUM_DPP__MAX];
	bool DynamicMetadataEnable[DC__NUM_DPP__MAX];
	int DynamicMetadataLinesBeforeActiveRequired[DC__NUM_DPP__MAX];
	unsigned int DynamicMetadataTransmittedBytes[DC__NUM_DPP__MAX];
	double DCCRate[DC__NUM_DPP__MAX];
	double AverageDCCCompressionRate;
	enum odm_combine_mode ODMCombineEnabled[DC__NUM_DPP__MAX];
	double OutputBpp[DC__NUM_DPP__MAX];
	bool DSCEnabled[DC__NUM_DPP__MAX];
	unsigned int DSCInputBitPerComponent[DC__NUM_DPP__MAX];
	enum output_format_class OutputFormat[DC__NUM_DPP__MAX];
	enum output_encoder_class Output[DC__NUM_DPP__MAX];
	unsigned int BlendingAndTiming[DC__NUM_DPP__MAX];
	bool SynchronizedVBlank;
	unsigned int NumberOfCursors[DC__NUM_DPP__MAX];
	unsigned int CursorWidth[DC__NUM_DPP__MAX][DC__NUM_CURSOR__MAX];
	unsigned int CursorBPP[DC__NUM_DPP__MAX][DC__NUM_CURSOR__MAX];
	bool XFCEnabled[DC__NUM_DPP__MAX];
	bool ScalerEnabled[DC__NUM_DPP__MAX];

	// Intermediates/Informational
	bool ImmediateFlipSupport;
	double DETBufferSizeY[DC__NUM_DPP__MAX];
	double DETBufferSizeC[DC__NUM_DPP__MAX];
	unsigned int SwathHeightY[DC__NUM_DPP__MAX];
	unsigned int SwathHeightC[DC__NUM_DPP__MAX];
	unsigned int LBBitPerPixel[DC__NUM_DPP__MAX];
	double LastPixelOfLineExtraWatermark;
	double TotalDataReadBandwidth;
	unsigned int TotalActiveWriteback;
	unsigned int EffectiveLBLatencyHidingSourceLinesLuma;
	unsigned int EffectiveLBLatencyHidingSourceLinesChroma;
	double BandwidthAvailableForImmediateFlip;
	unsigned int PrefetchMode[DC__VOLTAGE_STATES + 1][2];
	unsigned int PrefetchModePerState[DC__VOLTAGE_STATES + 1][2];
	unsigned int MinPrefetchMode;
	unsigned int MaxPrefetchMode;
	bool AnyLinesForVMOrRowTooLarge;
	double MaxVStartup;
	bool IgnoreViewportPositioning;
	bool ErrorResult[DC__NUM_DPP__MAX];
	//
	// Calculated dml_ml->vba.Outputs
	//
	double DCFCLKDeepSleep;
	double UrgentWatermark;
	double UrgentExtraLatency;
	double WritebackUrgentWatermark;
	double StutterExitWatermark;
	double StutterEnterPlusExitWatermark;
	double DRAMClockChangeWatermark;
	double WritebackDRAMClockChangeWatermark;
	double StutterEfficiency;
	double StutterEfficiencyNotIncludingVBlank;
	double NonUrgentLatencyTolerance;
	double MinActiveDRAMClockChangeLatencySupported;

	// These are the clocks calcuated by the library but they are not actually
	// used explicitly. They are fetched by tests and then possibly used. The
	// ultimate values to use are the ones specified by the parameters to DML
	double DISPCLK_calculated;
	double DPPCLK_calculated[DC__NUM_DPP__MAX];

	unsigned int VUpdateOffsetPix[DC__NUM_DPP__MAX];
	double VUpdateWidthPix[DC__NUM_DPP__MAX];
	double VReadyOffsetPix[DC__NUM_DPP__MAX];

	unsigned int TotImmediateFlipBytes;
	double TCalc;

	display_e2e_pipe_params_st cache_pipes[DC__NUM_DPP__MAX];
	unsigned int cache_num_pipes;
	unsigned int pipe_plane[DC__NUM_DPP__MAX];

	/* vba mode support */
	/*inputs*/
	bool EmbeddedPanel[DC__NUM_DPP__MAX];
	bool SupportGFX7CompatibleTilingIn32bppAnd64bpp;
	double MaxHSCLRatio;
	double MaxVSCLRatio;
	unsigned int MaxNumWriteback;
	bool WritebackLumaAndChromaScalingSupported;
	bool Cursor64BppSupport;
	double DCFCLKPerState[DC__VOLTAGE_STATES + 1];
	double DCFCLKState[DC__VOLTAGE_STATES + 1][2];
	double FabricClockPerState[DC__VOLTAGE_STATES + 1];
	double SOCCLKPerState[DC__VOLTAGE_STATES + 1];
	double PHYCLKPerState[DC__VOLTAGE_STATES + 1];
	double DTBCLKPerState[DC__VOLTAGE_STATES + 1];
	double MaxDppclk[DC__VOLTAGE_STATES + 1];
	double MaxDSCCLK[DC__VOLTAGE_STATES + 1];
	double DRAMSpeedPerState[DC__VOLTAGE_STATES + 1];
	double MaxDispclk[DC__VOLTAGE_STATES + 1];
	int VoltageOverrideLevel;

	/*outputs*/
	bool ScaleRatioAndTapsSupport;
	bool SourceFormatPixelAndScanSupport;
	double TotalBandwidthConsumedGBytePerSecond;
	bool DCCEnabledInAnyPlane;
	bool WritebackLatencySupport;
	bool WritebackModeSupport;
	bool Writeback10bpc420Supported;
	bool BandwidthSupport[DC__VOLTAGE_STATES + 1];
	unsigned int TotalNumberOfActiveWriteback;
	double CriticalPoint;
	double ReturnBWToDCNPerState;
	bool IsErrorResult[DC__VOLTAGE_STATES + 1][2][DC__NUM_DPP__MAX];
	bool prefetch_vm_bw_valid;
	bool prefetch_row_bw_valid;
	bool NumberOfOTGSupport;
	bool NonsupportedDSCInputBPC;
	bool WritebackScaleRatioAndTapsSupport;
	bool CursorSupport;
	bool PitchSupport;
	enum dm_validation_status ValidationStatus[DC__VOLTAGE_STATES + 1];

	double WritebackLineBufferLumaBufferSize;
	double WritebackLineBufferChromaBufferSize;
	double WritebackMinHSCLRatio;
	double WritebackMinVSCLRatio;
	double WritebackMaxHSCLRatio;
	double WritebackMaxVSCLRatio;
	double WritebackMaxHSCLTaps;
	double WritebackMaxVSCLTaps;
	unsigned int MaxNumDPP;
	unsigned int MaxNumOTG;
	double CursorBufferSize;
	double CursorChunkSize;
	unsigned int Mode;
	double OutputLinkDPLanes[DC__NUM_DPP__MAX];
	double ForcedOutputLinkBPP[DC__NUM_DPP__MAX]; // Mode Support only
	double ImmediateFlipBW[DC__NUM_DPP__MAX];
	double MaxMaxVStartup[DC__VOLTAGE_STATES + 1][2];

	double WritebackLumaVExtra;
	double WritebackChromaVExtra;
	double WritebackRequiredDISPCLK;
	double MaximumSwathWidthSupport;
	double MaximumSwathWidthInDETBuffer;
	double MaximumSwathWidthInLineBuffer;
	double MaxDispclkRoundedDownToDFSGranularity;
	double MaxDppclkRoundedDownToDFSGranularity;
	double PlaneRequiredDISPCLKWithoutODMCombine;
	double PlaneRequiredDISPCLKWithODMCombine;
	double PlaneRequiredDISPCLK;
	double TotalNumberOfActiveOTG;
	double FECOverhead;
	double EffectiveFECOverhead;
	double Outbpp;
	unsigned int OutbppDSC;
	double TotalDSCUnitsRequired;
	double bpp;
	unsigned int slices;
	double SwathWidthGranularityY;
	double RoundedUpMaxSwathSizeBytesY;
	double SwathWidthGranularityC;
	double RoundedUpMaxSwathSizeBytesC;
	double EffectiveDETLBLinesLuma;
	double EffectiveDETLBLinesChroma;
	double ProjectedDCFCLKDeepSleep[DC__VOLTAGE_STATES + 1][2];
	double PDEAndMetaPTEBytesPerFrameY;
	double PDEAndMetaPTEBytesPerFrameC;
	unsigned int MetaRowBytesY;
	unsigned int MetaRowBytesC;
	unsigned int DPTEBytesPerRowC;
	unsigned int DPTEBytesPerRowY;
	double ExtraLatency;
	double TimeCalc;
	double TWait;
	double MaximumReadBandwidthWithPrefetch;
	double MaximumReadBandwidthWithoutPrefetch;
	double total_dcn_read_bw_with_flip;
	double total_dcn_read_bw_with_flip_no_urgent_burst;
	double FractionOfUrgentBandwidth;
	double FractionOfUrgentBandwidthImmediateFlip; // Mode Support debugging output

	/* ms locals */
	double IdealSDPPortBandwidthPerState[DC__VOLTAGE_STATES + 1][2];
	unsigned int NoOfDPP[DC__VOLTAGE_STATES + 1][2][DC__NUM_DPP__MAX];
	int NoOfDPPThisState[DC__NUM_DPP__MAX];
	enum odm_combine_mode ODMCombineEnablePerState[DC__VOLTAGE_STATES + 1][DC__NUM_DPP__MAX];
	double SwathWidthYThisState[DC__NUM_DPP__MAX];
	unsigned int SwathHeightCPerState[DC__VOLTAGE_STATES + 1][2][DC__NUM_DPP__MAX];
	unsigned int SwathHeightYThisState[DC__NUM_DPP__MAX];
	unsigned int SwathHeightCThisState[DC__NUM_DPP__MAX];
	double VRatioPreY[DC__VOLTAGE_STATES + 1][2][DC__NUM_DPP__MAX];
	double VRatioPreC[DC__VOLTAGE_STATES + 1][2][DC__NUM_DPP__MAX];
	double RequiredPrefetchPixelDataBWLuma[DC__VOLTAGE_STATES + 1][2][DC__NUM_DPP__MAX];
	double RequiredPrefetchPixelDataBWChroma[DC__VOLTAGE_STATES + 1][2][DC__NUM_DPP__MAX];
	double RequiredDPPCLK[DC__VOLTAGE_STATES + 1][2][DC__NUM_DPP__MAX];
	double RequiredDPPCLKThisState[DC__NUM_DPP__MAX];
	bool PTEBufferSizeNotExceededY[DC__VOLTAGE_STATES + 1][2][DC__NUM_DPP__MAX];
	bool PTEBufferSizeNotExceededC[DC__VOLTAGE_STATES + 1][2][DC__NUM_DPP__MAX];
	bool BandwidthWithoutPrefetchSupported[DC__VOLTAGE_STATES + 1][2];
	bool PrefetchSupported[DC__VOLTAGE_STATES + 1][2];
	bool VRatioInPrefetchSupported[DC__VOLTAGE_STATES + 1][2];
	double RequiredDISPCLK[DC__VOLTAGE_STATES + 1][2];
	bool DISPCLK_DPPCLK_Support[DC__VOLTAGE_STATES + 1][2];
	bool TotalAvailablePipesSupport[DC__VOLTAGE_STATES + 1][2];
	unsigned int TotalNumberOfActiveDPP[DC__VOLTAGE_STATES + 1][2];
	unsigned int TotalNumberOfDCCActiveDPP[DC__VOLTAGE_STATES + 1][2];
	bool ModeSupport[DC__VOLTAGE_STATES + 1][2];
	double ReturnBWPerState[DC__VOLTAGE_STATES + 1][2];
	bool DIOSupport[DC__VOLTAGE_STATES + 1];
	bool NotEnoughDSCUnits[DC__VOLTAGE_STATES + 1];
	bool DSCCLKRequiredMoreThanSupported[DC__VOLTAGE_STATES + 1];
	bool DTBCLKRequiredMoreThanSupported[DC__VOLTAGE_STATES + 1];
	double UrgentRoundTripAndOutOfOrderLatencyPerState[DC__VOLTAGE_STATES + 1];
	bool ROBSupport[DC__VOLTAGE_STATES + 1][2];
	bool PTEBufferSizeNotExceeded[DC__VOLTAGE_STATES + 1][2];
	bool TotalVerticalActiveBandwidthSupport[DC__VOLTAGE_STATES + 1][2];
	double MaxTotalVerticalActiveAvailableBandwidth[DC__VOLTAGE_STATES + 1][2];
	double PrefetchBW[DC__NUM_DPP__MAX];
	double PDEAndMetaPTEBytesPerFrame[DC__VOLTAGE_STATES + 1][2][DC__NUM_DPP__MAX];
	double MetaRowBytes[DC__VOLTAGE_STATES + 1][2][DC__NUM_DPP__MAX];
	double DPTEBytesPerRow[DC__VOLTAGE_STATES + 1][2][DC__NUM_DPP__MAX];
	double PrefetchLinesY[DC__VOLTAGE_STATES + 1][2][DC__NUM_DPP__MAX];
	double PrefetchLinesC[DC__VOLTAGE_STATES + 1][2][DC__NUM_DPP__MAX];
	unsigned int MaxNumSwY[DC__NUM_DPP__MAX];
	unsigned int MaxNumSwC[DC__NUM_DPP__MAX];
	double PrefillY[DC__NUM_DPP__MAX];
	double PrefillC[DC__NUM_DPP__MAX];
	double LineTimesForPrefetch[DC__NUM_DPP__MAX];
	double LinesForMetaPTE[DC__NUM_DPP__MAX];
	double LinesForMetaAndDPTERow[DC__NUM_DPP__MAX];
	double MinDPPCLKUsingSingleDPP[DC__NUM_DPP__MAX];
	double SwathWidthYSingleDPP[DC__NUM_DPP__MAX];
	double BytePerPixelInDETY[DC__NUM_DPP__MAX];
	double BytePerPixelInDETC[DC__NUM_DPP__MAX];
	bool RequiresDSC[DC__VOLTAGE_STATES + 1][DC__NUM_DPP__MAX];
	unsigned int NumberOfDSCSlice[DC__VOLTAGE_STATES + 1][DC__NUM_DPP__MAX];
	double RequiresFEC[DC__VOLTAGE_STATES + 1][DC__NUM_DPP__MAX];
	double OutputBppPerState[DC__VOLTAGE_STATES + 1][DC__NUM_DPP__MAX];
	double DSCDelayPerState[DC__VOLTAGE_STATES + 1][DC__NUM_DPP__MAX];
	bool ViewportSizeSupport[DC__VOLTAGE_STATES + 1][2];
	unsigned int Read256BlockHeightY[DC__NUM_DPP__MAX];
	unsigned int Read256BlockWidthY[DC__NUM_DPP__MAX];
	unsigned int Read256BlockHeightC[DC__NUM_DPP__MAX];
	unsigned int Read256BlockWidthC[DC__NUM_DPP__MAX];
	double MaxSwathHeightY[DC__NUM_DPP__MAX];
	double MaxSwathHeightC[DC__NUM_DPP__MAX];
	double MinSwathHeightY[DC__NUM_DPP__MAX];
	double MinSwathHeightC[DC__NUM_DPP__MAX];
	double ReadBandwidthLuma[DC__NUM_DPP__MAX];
	double ReadBandwidthChroma[DC__NUM_DPP__MAX];
	double ReadBandwidth[DC__NUM_DPP__MAX];
	double WriteBandwidth[DC__NUM_DPP__MAX];
	double PSCL_FACTOR[DC__NUM_DPP__MAX];
	double PSCL_FACTOR_CHROMA[DC__NUM_DPP__MAX];
	double MaximumVStartup[DC__VOLTAGE_STATES + 1][2][DC__NUM_DPP__MAX];
	unsigned int MacroTileWidthY[DC__NUM_DPP__MAX];
	unsigned int MacroTileWidthC[DC__NUM_DPP__MAX];
	double AlignedDCCMetaPitch[DC__NUM_DPP__MAX];
	double AlignedYPitch[DC__NUM_DPP__MAX];
	double AlignedCPitch[DC__NUM_DPP__MAX];
	double MaximumSwathWidth[DC__NUM_DPP__MAX];
	double cursor_bw[DC__NUM_DPP__MAX];
	double cursor_bw_pre[DC__NUM_DPP__MAX];
	double Tno_bw[DC__NUM_DPP__MAX];
	double prefetch_vmrow_bw[DC__NUM_DPP__MAX];
	double DestinationLinesToRequestVMInImmediateFlip[DC__NUM_DPP__MAX];
	double DestinationLinesToRequestRowInImmediateFlip[DC__NUM_DPP__MAX];
	double final_flip_bw[DC__NUM_DPP__MAX];
	bool ImmediateFlipSupportedForState[DC__VOLTAGE_STATES + 1][2];
	double WritebackDelay[DC__VOLTAGE_STATES + 1][DC__NUM_DPP__MAX];
	unsigned int vm_group_bytes[DC__NUM_DPP__MAX];
	unsigned int dpte_group_bytes[DC__NUM_DPP__MAX];
	unsigned int dpte_row_height[DC__NUM_DPP__MAX];
	unsigned int meta_req_height[DC__NUM_DPP__MAX];
	unsigned int meta_req_width[DC__NUM_DPP__MAX];
	unsigned int meta_row_height[DC__NUM_DPP__MAX];
	unsigned int meta_row_width[DC__NUM_DPP__MAX];
	unsigned int dpte_row_height_chroma[DC__NUM_DPP__MAX];
	unsigned int meta_req_height_chroma[DC__NUM_DPP__MAX];
	unsigned int meta_req_width_chroma[DC__NUM_DPP__MAX];
	unsigned int meta_row_height_chroma[DC__NUM_DPP__MAX];
	unsigned int meta_row_width_chroma[DC__NUM_DPP__MAX];
	bool ImmediateFlipSupportedForPipe[DC__NUM_DPP__MAX];
	double meta_row_bw[DC__NUM_DPP__MAX];
	double dpte_row_bw[DC__NUM_DPP__MAX];
	double DisplayPipeLineDeliveryTimeLuma[DC__NUM_DPP__MAX];                     // WM
	double DisplayPipeLineDeliveryTimeChroma[DC__NUM_DPP__MAX];                     // WM
	double DisplayPipeRequestDeliveryTimeLuma[DC__NUM_DPP__MAX];
	double DisplayPipeRequestDeliveryTimeChroma[DC__NUM_DPP__MAX];
	enum clock_change_support DRAMClockChangeSupport[DC__VOLTAGE_STATES + 1][2];
	double UrgentBurstFactorCursor[DC__NUM_DPP__MAX];
	double UrgentBurstFactorCursorPre[DC__NUM_DPP__MAX];
	double UrgentBurstFactorLuma[DC__NUM_DPP__MAX];
	double UrgentBurstFactorLumaPre[DC__NUM_DPP__MAX];
	double UrgentBurstFactorChroma[DC__NUM_DPP__MAX];
	double UrgentBurstFactorChromaPre[DC__NUM_DPP__MAX];


	bool           MPCCombine[DC__VOLTAGE_STATES + 1][2][DC__NUM_DPP__MAX];
	double         SwathWidthCSingleDPP[DC__NUM_DPP__MAX];
	double         MaximumSwathWidthInLineBufferLuma;
	double         MaximumSwathWidthInLineBufferChroma;
	double         MaximumSwathWidthLuma[DC__NUM_DPP__MAX];
	double         MaximumSwathWidthChroma[DC__NUM_DPP__MAX];
	enum odm_combine_mode odm_combine_dummy[DC__NUM_DPP__MAX];
	double         dummy1[DC__NUM_DPP__MAX];
	double         dummy2[DC__NUM_DPP__MAX];
	double         dummy3[DC__NUM_DPP__MAX];
	double         dummy4[DC__NUM_DPP__MAX];
	double         dummy5;
	double         dummy6;
	double         dummy7[DC__NUM_DPP__MAX];
	double         dummy8[DC__NUM_DPP__MAX];
	unsigned int        dummyinteger1ms[DC__NUM_DPP__MAX];
	double        dummyinteger2ms[DC__NUM_DPP__MAX];
	unsigned int        dummyinteger3[DC__NUM_DPP__MAX];
	unsigned int        dummyinteger4[DC__NUM_DPP__MAX];
	unsigned int        dummyinteger5;
	unsigned int        dummyinteger6;
	unsigned int        dummyinteger7;
	unsigned int        dummyinteger8;
	unsigned int        dummyinteger9;
	unsigned int        dummyinteger10;
	unsigned int        dummyinteger11;
	unsigned int        dummyinteger12;
	unsigned int        dummyintegerarr1[DC__NUM_DPP__MAX];
	unsigned int        dummyintegerarr2[DC__NUM_DPP__MAX];
	unsigned int        dummyintegerarr3[DC__NUM_DPP__MAX];
	unsigned int        dummyintegerarr4[DC__NUM_DPP__MAX];
	bool           dummysinglestring;
	bool           SingleDPPViewportSizeSupportPerPlane[DC__NUM_DPP__MAX];
	double         PlaneRequiredDISPCLKWithODMCombine2To1;
	double         PlaneRequiredDISPCLKWithODMCombine4To1;
	unsigned int   TotalNumberOfSingleDPPPlanes[DC__VOLTAGE_STATES + 1][2];
	bool           LinkDSCEnable;
	bool           ODMCombine4To1SupportCheckOK[DC__VOLTAGE_STATES + 1];
	enum odm_combine_mode ODMCombineEnableThisState[DC__NUM_DPP__MAX];
	double   SwathWidthCThisState[DC__NUM_DPP__MAX];
	bool           ViewportSizeSupportPerPlane[DC__NUM_DPP__MAX];
	double         AlignedDCCMetaPitchY[DC__NUM_DPP__MAX];
	double         AlignedDCCMetaPitchC[DC__NUM_DPP__MAX];

	unsigned int NotEnoughUrgentLatencyHiding;
	unsigned int NotEnoughUrgentLatencyHidingPre;
	int PTEBufferSizeInRequestsForLuma;
	int PTEBufferSizeInRequestsForChroma;

	// Missing from VBA
	int dpte_group_bytes_chroma;
	unsigned int vm_group_bytes_chroma;
	double dst_x_after_scaler;
	double dst_y_after_scaler;
	unsigned int VStartupRequiredWhenNotEnoughTimeForDynamicMetadata;

	/* perf locals*/
	double PrefetchBandwidth[DC__NUM_DPP__MAX];
	double VInitPreFillY[DC__NUM_DPP__MAX];
	double VInitPreFillC[DC__NUM_DPP__MAX];
	unsigned int MaxNumSwathY[DC__NUM_DPP__MAX];
	unsigned int MaxNumSwathC[DC__NUM_DPP__MAX];
	unsigned int VStartup[DC__NUM_DPP__MAX];
	double DSTYAfterScaler[DC__NUM_DPP__MAX];
	double DSTXAfterScaler[DC__NUM_DPP__MAX];
	bool AllowDRAMClockChangeDuringVBlank[DC__NUM_DPP__MAX];
	bool AllowDRAMSelfRefreshDuringVBlank[DC__NUM_DPP__MAX];
	double VRatioPrefetchY[DC__NUM_DPP__MAX];
	double VRatioPrefetchC[DC__NUM_DPP__MAX];
	double DestinationLinesForPrefetch[DC__NUM_DPP__MAX];
	double DestinationLinesToRequestVMInVBlank[DC__NUM_DPP__MAX];
	double DestinationLinesToRequestRowInVBlank[DC__NUM_DPP__MAX];
	double MinTTUVBlank[DC__NUM_DPP__MAX];
	double BytePerPixelDETY[DC__NUM_DPP__MAX];
	double BytePerPixelDETC[DC__NUM_DPP__MAX];
	double SwathWidthY[DC__NUM_DPP__MAX];
	double SwathWidthSingleDPPY[DC__NUM_DPP__MAX];
	double CursorRequestDeliveryTime[DC__NUM_DPP__MAX];
	double CursorRequestDeliveryTimePrefetch[DC__NUM_DPP__MAX];
	double ReadBandwidthPlaneLuma[DC__NUM_DPP__MAX];
	double ReadBandwidthPlaneChroma[DC__NUM_DPP__MAX];
	double DisplayPipeLineDeliveryTimeLumaPrefetch[DC__NUM_DPP__MAX];
	double DisplayPipeLineDeliveryTimeChromaPrefetch[DC__NUM_DPP__MAX];
	double DisplayPipeRequestDeliveryTimeLumaPrefetch[DC__NUM_DPP__MAX];
	double DisplayPipeRequestDeliveryTimeChromaPrefetch[DC__NUM_DPP__MAX];
	double PixelPTEBytesPerRow[DC__NUM_DPP__MAX];
	double PDEAndMetaPTEBytesFrame[DC__NUM_DPP__MAX];
	double MetaRowByte[DC__NUM_DPP__MAX];
	double PrefetchSourceLinesY[DC__NUM_DPP__MAX];
	double RequiredPrefetchPixDataBWLuma[DC__NUM_DPP__MAX];
	double RequiredPrefetchPixDataBWChroma[DC__NUM_DPP__MAX];
	double PrefetchSourceLinesC[DC__NUM_DPP__MAX];
	double PSCL_THROUGHPUT_LUMA[DC__NUM_DPP__MAX];
	double PSCL_THROUGHPUT_CHROMA[DC__NUM_DPP__MAX];
	double DSCCLK_calculated[DC__NUM_DPP__MAX];
	unsigned int DSCDelay[DC__NUM_DPP__MAX];
	unsigned int MaxVStartupLines[DC__NUM_DPP__MAX];
	double DPPCLKUsingSingleDPP[DC__NUM_DPP__MAX];
	double DPPCLK[DC__NUM_DPP__MAX];
	unsigned int DCCYMaxUncompressedBlock[DC__NUM_DPP__MAX];
	unsigned int DCCYMaxCompressedBlock[DC__NUM_DPP__MAX];
	unsigned int DCCYIndependent64ByteBlock[DC__NUM_DPP__MAX];
	double MaximumDCCCompressionYSurface[DC__NUM_DPP__MAX];
	unsigned int BlockHeight256BytesY[DC__NUM_DPP__MAX];
	unsigned int BlockHeight256BytesC[DC__NUM_DPP__MAX];
	unsigned int BlockWidth256BytesY[DC__NUM_DPP__MAX];
	unsigned int BlockWidth256BytesC[DC__NUM_DPP__MAX];
	double XFCSlaveVUpdateOffset[DC__NUM_DPP__MAX];
	double XFCSlaveVupdateWidth[DC__NUM_DPP__MAX];
	double XFCSlaveVReadyOffset[DC__NUM_DPP__MAX];
	double XFCTransferDelay[DC__NUM_DPP__MAX];
	double XFCPrechargeDelay[DC__NUM_DPP__MAX];
	double XFCRemoteSurfaceFlipLatency[DC__NUM_DPP__MAX];
	double XFCPrefetchMargin[DC__NUM_DPP__MAX];
	unsigned int dpte_row_width_luma_ub[DC__NUM_DPP__MAX];
	unsigned int dpte_row_width_chroma_ub[DC__NUM_DPP__MAX];
	double FullDETBufferingTimeY[DC__NUM_DPP__MAX];                     // WM
	double FullDETBufferingTimeC[DC__NUM_DPP__MAX];                     // WM
	double DST_Y_PER_PTE_ROW_NOM_L[DC__NUM_DPP__MAX];
	double DST_Y_PER_PTE_ROW_NOM_C[DC__NUM_DPP__MAX];
	double DST_Y_PER_META_ROW_NOM_L[DC__NUM_DPP__MAX];
	double TimePerMetaChunkNominal[DC__NUM_DPP__MAX];
	double TimePerMetaChunkVBlank[DC__NUM_DPP__MAX];
	double TimePerMetaChunkFlip[DC__NUM_DPP__MAX];
	unsigned int swath_width_luma_ub[DC__NUM_DPP__MAX];
	unsigned int swath_width_chroma_ub[DC__NUM_DPP__MAX];
	unsigned int PixelPTEReqWidthY[DC__NUM_DPP__MAX];
	unsigned int PixelPTEReqHeightY[DC__NUM_DPP__MAX];
	unsigned int PTERequestSizeY[DC__NUM_DPP__MAX];
	unsigned int PixelPTEReqWidthC[DC__NUM_DPP__MAX];
	unsigned int PixelPTEReqHeightC[DC__NUM_DPP__MAX];
	unsigned int PTERequestSizeC[DC__NUM_DPP__MAX];
	double time_per_pte_group_nom_luma[DC__NUM_DPP__MAX];
	double time_per_pte_group_nom_chroma[DC__NUM_DPP__MAX];
	double time_per_pte_group_vblank_luma[DC__NUM_DPP__MAX];
	double time_per_pte_group_vblank_chroma[DC__NUM_DPP__MAX];
	double time_per_pte_group_flip_luma[DC__NUM_DPP__MAX];
	double time_per_pte_group_flip_chroma[DC__NUM_DPP__MAX];
	double TimePerVMGroupVBlank[DC__NUM_DPP__MAX];
	double TimePerVMGroupFlip[DC__NUM_DPP__MAX];
	double TimePerVMRequestVBlank[DC__NUM_DPP__MAX];
	double TimePerVMRequestFlip[DC__NUM_DPP__MAX];
	unsigned int dpde0_bytes_per_frame_ub_l[DC__NUM_DPP__MAX];
	unsigned int meta_pte_bytes_per_frame_ub_l[DC__NUM_DPP__MAX];
	unsigned int dpde0_bytes_per_frame_ub_c[DC__NUM_DPP__MAX];
	unsigned int meta_pte_bytes_per_frame_ub_c[DC__NUM_DPP__MAX];
	double LinesToFinishSwathTransferStutterCriticalPlane;
	unsigned int BytePerPixelYCriticalPlane;
	double SwathWidthYCriticalPlane;
	double LinesInDETY[DC__NUM_DPP__MAX];
	double LinesInDETYRoundedDownToSwath[DC__NUM_DPP__MAX];

	double SwathWidthSingleDPPC[DC__NUM_DPP__MAX];
	double SwathWidthC[DC__NUM_DPP__MAX];
	unsigned int BytePerPixelY[DC__NUM_DPP__MAX];
	unsigned int BytePerPixelC[DC__NUM_DPP__MAX];
	long dummyinteger1;
	long dummyinteger2;
	double FinalDRAMClockChangeLatency;
	double Tdmdl_vm[DC__NUM_DPP__MAX];
	double Tdmdl[DC__NUM_DPP__MAX];
	unsigned int ThisVStartup;
	bool WritebackAllowDRAMClockChangeEndPosition[DC__NUM_DPP__MAX];
	double DST_Y_PER_META_ROW_NOM_C[DC__NUM_DPP__MAX];
	double TimePerChromaMetaChunkNominal[DC__NUM_DPP__MAX];
	double TimePerChromaMetaChunkVBlank[DC__NUM_DPP__MAX];
	double TimePerChromaMetaChunkFlip[DC__NUM_DPP__MAX];
	unsigned int DCCCMaxUncompressedBlock[DC__NUM_DPP__MAX];
	unsigned int DCCCMaxCompressedBlock[DC__NUM_DPP__MAX];
	unsigned int DCCCIndependent64ByteBlock[DC__NUM_DPP__MAX];
	double VStartupMargin;
	bool NotEnoughTimeForDynamicMetadata;

	/* Missing from VBA */
	unsigned int MaximumMaxVStartupLines;
	double FabricAndDRAMBandwidth;
	double LinesInDETLuma;
	double LinesInDETChroma;
	unsigned int ImmediateFlipBytes[DC__NUM_DPP__MAX];
	unsigned int LinesInDETC[DC__NUM_DPP__MAX];
	unsigned int LinesInDETCRoundedDownToSwath[DC__NUM_DPP__MAX];
	double UrgentLatencySupportUsPerState[DC__VOLTAGE_STATES + 1][2][DC__NUM_DPP__MAX];
	double UrgentLatencySupportUs[DC__NUM_DPP__MAX];
	double FabricAndDRAMBandwidthPerState[DC__VOLTAGE_STATES + 1];
	bool UrgentLatencySupport[DC__VOLTAGE_STATES + 1][2];
	unsigned int SwathWidthYPerState[DC__VOLTAGE_STATES + 1][2][DC__NUM_DPP__MAX];
	unsigned int SwathHeightYPerState[DC__VOLTAGE_STATES + 1][2][DC__NUM_DPP__MAX];
	double qual_row_bw[DC__NUM_DPP__MAX];
	double prefetch_row_bw[DC__NUM_DPP__MAX];
	double prefetch_vm_bw[DC__NUM_DPP__MAX];

	double PTEGroupSize;
	unsigned int PDEProcessingBufIn64KBReqs;

	double MaxTotalVActiveRDBandwidth;
	bool DoUrgentLatencyAdjustment;
	double UrgentLatencyAdjustmentFabricClockComponent;
	double UrgentLatencyAdjustmentFabricClockReference;
	double MinUrgentLatencySupportUs;
	double MinFullDETBufferingTime;
	double AverageReadBandwidthGBytePerSecond;
	bool   FirstMainPlane;

	unsigned int ViewportWidthChroma[DC__NUM_DPP__MAX];
	unsigned int ViewportHeightChroma[DC__NUM_DPP__MAX];
	double HRatioChroma[DC__NUM_DPP__MAX];
	double VRatioChroma[DC__NUM_DPP__MAX];
	int WritebackSourceWidth[DC__NUM_DPP__MAX];

	bool ModeIsSupported;
	bool ODMCombine4To1Supported;

	unsigned int SurfaceWidthY[DC__NUM_DPP__MAX];
	unsigned int SurfaceWidthC[DC__NUM_DPP__MAX];
	unsigned int SurfaceHeightY[DC__NUM_DPP__MAX];
	unsigned int SurfaceHeightC[DC__NUM_DPP__MAX];
	unsigned int WritebackHTaps[DC__NUM_DPP__MAX];
	unsigned int WritebackVTaps[DC__NUM_DPP__MAX];
	bool DSCEnable[DC__NUM_DPP__MAX];

	double DRAMClockChangeLatencyOverride;

	double GPUVMMinPageSize;
	double HostVMMinPageSize;

	bool   MPCCombineEnable[DC__NUM_DPP__MAX];
	unsigned int HostVMMaxNonCachedPageTableLevels;
	bool   DynamicMetadataVMEnabled;
	double       WritebackInterfaceBufferSize;
	double       WritebackLineBufferSize;

	double DCCRateLuma[DC__NUM_DPP__MAX];
	double DCCRateChroma[DC__NUM_DPP__MAX];

	double PHYCLKD18PerState[DC__VOLTAGE_STATES + 1];
	int MinVoltageLevel;
	int MaxVoltageLevel;

	bool WritebackSupportInterleaveAndUsingWholeBufferForASingleStream;
	bool NumberOfHDMIFRLSupport;
	unsigned int MaxNumHDMIFRLOutputs;
	int    AudioSampleRate[DC__NUM_DPP__MAX];
	int    AudioSampleLayout[DC__NUM_DPP__MAX];

	int PercentMarginOverMinimumRequiredDCFCLK;
	bool DynamicMetadataSupported[DC__VOLTAGE_STATES + 1][2];
	enum immediate_flip_requirement ImmediateFlipRequirement;
	double DETBufferSizeYThisState[DC__NUM_DPP__MAX];
	double DETBufferSizeCThisState[DC__NUM_DPP__MAX];
	bool NoUrgentLatencyHiding[DC__NUM_DPP__MAX];
	bool NoUrgentLatencyHidingPre[DC__NUM_DPP__MAX];
	int swath_width_luma_ub_this_state[DC__NUM_DPP__MAX];
	int swath_width_chroma_ub_this_state[DC__NUM_DPP__MAX];
	double UrgLatency[DC__VOLTAGE_STATES + 1];
	double VActiveCursorBandwidth[DC__VOLTAGE_STATES + 1][2][DC__NUM_DPP__MAX];
	double VActivePixelBandwidth[DC__VOLTAGE_STATES + 1][2][DC__NUM_DPP__MAX];
	bool NoTimeForPrefetch[DC__VOLTAGE_STATES + 1][2][DC__NUM_DPP__MAX];
	bool NoTimeForDynamicMetadata[DC__VOLTAGE_STATES + 1][2][DC__NUM_DPP__MAX];
	double dpte_row_bandwidth[DC__VOLTAGE_STATES + 1][2][DC__NUM_DPP__MAX];
	double meta_row_bandwidth[DC__VOLTAGE_STATES + 1][2][DC__NUM_DPP__MAX];
	double DETBufferSizeYAllStates[DC__VOLTAGE_STATES + 1][2][DC__NUM_DPP__MAX];
	double DETBufferSizeCAllStates[DC__VOLTAGE_STATES + 1][2][DC__NUM_DPP__MAX];
	int swath_width_luma_ub_all_states[DC__VOLTAGE_STATES + 1][2][DC__NUM_DPP__MAX];
	int swath_width_chroma_ub_all_states[DC__VOLTAGE_STATES + 1][2][DC__NUM_DPP__MAX];
	bool NotUrgentLatencyHiding[DC__VOLTAGE_STATES + 1][2];
	unsigned int SwathHeightYAllStates[DC__VOLTAGE_STATES + 1][2][DC__NUM_DPP__MAX];
	unsigned int SwathHeightCAllStates[DC__VOLTAGE_STATES + 1][2][DC__NUM_DPP__MAX];
	unsigned int SwathWidthYAllStates[DC__VOLTAGE_STATES + 1][2][DC__NUM_DPP__MAX];
	unsigned int SwathWidthCAllStates[DC__VOLTAGE_STATES + 1][2][DC__NUM_DPP__MAX];
	double TotalDPTERowBandwidth[DC__VOLTAGE_STATES + 1][2];
	double TotalMetaRowBandwidth[DC__VOLTAGE_STATES + 1][2];
	double TotalVActiveCursorBandwidth[DC__VOLTAGE_STATES + 1][2];
	double TotalVActivePixelBandwidth[DC__VOLTAGE_STATES + 1][2];
	bool UseMinimumRequiredDCFCLK;
	double WritebackDelayTime[DC__NUM_DPP__MAX];
	unsigned int DCCYIndependentBlock[DC__NUM_DPP__MAX];
	unsigned int DCCCIndependentBlock[DC__NUM_DPP__MAX];
	unsigned int dummyinteger15;
	unsigned int dummyinteger16;
	unsigned int dummyinteger17;
	unsigned int dummyinteger18;
	unsigned int dummyinteger19;
	unsigned int dummyinteger20;
	unsigned int dummyinteger21;
	unsigned int dummyinteger22;
	unsigned int dummyinteger23;
	unsigned int dummyinteger24;
	unsigned int dummyinteger25;
	unsigned int dummyinteger26;
	unsigned int dummyinteger27;
	unsigned int dummyinteger28;
	unsigned int dummyinteger29;
	bool dummystring[DC__NUM_DPP__MAX];
	double BPP;
	enum odm_combine_policy ODMCombinePolicy;
};

bool CalculateMinAndMaxPrefetchMode(
		enum self_refresh_affinity AllowDRAMSelfRefreshOrDRAMClockChangeInVblank,
		unsigned int *MinPrefetchMode,
		unsigned int *MaxPrefetchMode);

double CalculateWriteBackDISPCLK(
		enum source_format_class WritebackPixelFormat,
		double PixelClock,
		double WritebackHRatio,
		double WritebackVRatio,
		unsigned int WritebackLumaHTaps,
		unsigned int WritebackLumaVTaps,
		unsigned int WritebackChromaHTaps,
		unsigned int WritebackChromaVTaps,
		double WritebackDestinationWidth,
		unsigned int HTotal,
		unsigned int WritebackChromaLineBufferWidth);

#endif /* _DML2_DISPLAY_MODE_VBA_H_ */
