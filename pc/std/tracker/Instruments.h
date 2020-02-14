#pragma once
#include <stdint.h>
#include "shared/Brr.h"
#include "gui/Text_Edit_Rect.h"
#include "gui/Text.h"
#include "gui/Button.h"
/* Represents volume level of sample, that is also the raw volume written
 * to SNES APU DSP register */
struct DspVol
{
  uint8_t vol  :7;
  uint8_t phase :1; // sign
} __attribute__((packed));

/* Used for variables that will involve their value written to the SNES
 * APU DSP Pitch register. Even if certain variables are not directly
 * written to the register, it helps to keep them in the same format. */
struct DspPitch
{
  union {
    uint16_t pitch :14;
    struct {
      uint8_t pitch_l;
      uint8_t pitch_h :6;
    };
  };
} __attribute__((packed));

/* Used for instrument ADSR settings. This data structure is the same
 * format as will be written to the two SNES APU DSP ADSR registers */
struct Adsr
{
  // raw adsr reg values
  uint8_t sustain_rate :4;
  uint8_t sustain_level :4;
  uint8_t attack_rate :4;
  uint8_t decay_rate :3;
  uint8_t adsr_active :1;
} __attribute__((packed));

/* This sample number is hardcoded for now until sucessful testing is
 * done. Later, it will be made so that the limit can be dynamically
 * increased */
#define NUM_SAMPLES 0x10
#define SAMPLE_NAME_MAXLEN 128
#define SNES_MAX_VOL 0x7f

struct Sample
{
  char name[SAMPLE_NAME_MAXLEN]; // name of the sample
  /* pointer to first BRR block. can act as an iterator until end block is
   * found */
  Brr *brr; // raw brr sample data. Have to iterate it to END block
  /* offset into sample where loop starts, specified by number of BRR
   * blocks or [by samples and must be divisible by 16]*/
  uint16_t rel_loop;
  /* signed offset in semitones to pitch the sample. This will be used
   * directly by the SNES driver. The tracker must impose the restraints
   * on the range allowed */
  //int8_t semitone_offset;
  //DspPitch fine_tune; // used to pitch the sample for range of +/- one semitone
private:
  /* The raw stereo volume that will be calculated from the sample /
   * instrument volume and panning settings. This might be something that
   * is actually calculated from the SNES driver and will be removed from
   * here*/
  //DspVol vol_l, vol_r;
};

/* This sample number is hardcoded for now until sucessful testing is
 * done. Later, it will be made so that the limit can be dynamically
 * increased */
#define NUM_INSTR 0x10
#define INSTR_NAME_MAXLEN 128

struct Instrument
{
  char name[INSTR_NAME_MAXLEN]; // the name of the instrument
  Sample samples[NUM_SAMPLES]; // the raw BRR sample
  /* signed offset in semitones to pitch the sample. This will be used
   * directly by the SNES driver. The tracker must impose the restraints
   * on the range allowed */
  int8_t semitone_offset;
  /* used to pitch the sample for range of +/- one semitone. Tracker
   * software must impose retraints on the allowed range of values. Will
   * be used by SNES Driver */
  DspPitch fine_tune;
  /* 0x80 = dead center, 0xFF = hard right, 0x00 = hard left */
  int8_t pan;
  Adsr adsr; // The volume envelope that will be used for this instrument
  /* Aside from the ADSR hardware volume envelope, the voice stereo volume
   * may be adjusted real-time for additional effects.*/
  /* Note on volume envelopes as I learned from Milky Tracker. The graph
   * view X-axis is specified in ticks, up to 0x100 ticks. So each point
   * of the envelope is also specified in ticks */
  //VolumeEnvelope ve;
  //PanEnvelope pe;
};


/* That defined the Data model above. Now time to get that into a view */
struct Instrument_Panel
{
  Instrument_Panel(Instrument *instruments);
  void event_handler(SDL_Event &ev);
  void draw();

  Text title;
  Button load, save, zap;
  Text_Edit_Rect instr_name[NUM_INSTR]; // temporarily hard coding the number of instruments
  Instrument *instruments;
};

struct Sample_Panel
{
  void event_handler(const SDL_Event &ev);
  void draw();
  Text title;
  Button load, save;
  Text_Edit_Rect *sample_name[NUM_SAMPLES];
};

/* {
  Instrument instruments[0x10];
};*/