/*
 * Copyright (c) 2016 Clyde Stanfield
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */
#ifndef __NYRA_EMU_NES_HEADER_H__
#define __NYRA_EMU_NES_HEADER_H__

#include <string>
#include <vector>
#include <ostream>
#include <nyra/emu/nes/Constants.h>
#include <nyra/core/Archive.h>

namespace nyra
{
namespace emu
{
namespace nes
{
/*
 *  \class Header
 *  \brief In memory representation of the iNES header. The iNES header
 *         describes the ROM format.
 *         Header information from:
 *         https://wiki.nesdev.com/w/index.php/INES
 */
class Header
{
public:
    /*
     *  \func Constructor
     *  \brief Creates a default header. A header created in this way
     *         is invalid. You must call initialize for it to be valid.
     */
    Header();

    /*
     *  \func Constructor
     *  \brief Sets up a header based on the binary information in the file.
     *         This constructs a valid header object.
     *
     *  \param binary The bytes in the file. You can pass in the entire file.
     *         You must pass in at least getHeaderSize() bytes.
     */
    Header(const std::vector<uint8_t>& binary);

    /*
     *  \func initialize
     *  \brief Sets up a header based on the binary information in the file.
     *         The header is valid after calling initialize.
     *
     *  \param binary The bytes in the file. You can pass in the entire file.
     *         You must pass in at least getHeaderSize() bytes.
     */
    void initialize(const std::vector<uint8_t>& binary);

    /*
     *  \func getProgRomSize
     *  \brief Gets the number of 16384 sized bytes of Prog ROM.
     *
     *  \return The number of Prog ROM banks
     */
    inline size_t getProgRomSize() const
    {
        return mProgSize;
    }

    /*
     *  \func getChrRomSize
     *  \brief Gets the number of 8192 sized bytes of Chr ROM.
     *
     *  \return The number of Chr ROM banks
     */
    inline size_t getChrRomSize() const
    {
        return mChrRomSize;
    }

    /*
     *  \func getMapperNumber
     *  \brief Gets the mapper number. Common mapper numbers:
     *         TODO: Make enum for mappers
     *         iNES Mapper   Common Designation(s)
     *                   0   NROM
     *                   1   SxROM, MMC1
     *                   2   UxROM
     *                   3   CNROM
     *                   4   TxROM, MMC3, MMC6
     *                   5   ExROM, MMC5
     *                   7   AxROM
     *                   9   PxROM, MMC2
     *                   10  FxROM, MMC4
     *                   11  Color Dreams
     *                   13  CPROM
     *                   15  100-in-1 Contra Function 16 Multicart
     *                   16  Bandai EPROM (24C02)
     *                   18  Jaleco SS8806
     *                   19  Namco 163
     *                   21  VRC4a, VRC4c
     *                   22  VRC2a
     *                   23  VRC2b, VRC4e
     *                   24  VRC6a
     *                   25  VRC4b, VRC4d
     *                   26  VRC6b
     *                   34  BNROM, NINA-001
     *                   64  RAMBO-1
     *                   66  GxROM, MxROM
     *                   68  After Burner
     *                   69  FME-7, Sunsoft 5B
     *                   71  Camerica/Codemasters
     *                   73  VRC3
     *                   74  Pirate MMC3 derivative
     *                   75  VRC1
     *                   76  Namco 109 variant
     *                   79  NINA-03/NINA-06
     *                   85  VRC7
     *                   86  JALECO-JF-13
     *                   94  Senjou no Ookami
     *                   105 NES-EVENT
     *                   113 NINA-03/NINA-06??
     *                   118 TxSROM, MMC3
     *                   119 TQROM, MMC3
     *                   159 Bandai EPROM (24C01)
     *                   166 SUBOR
     *                   167 SUBOR
     *                   180 Crazy Climber
     *                   185 CNROM with protection diodes
     *                   192 Pirate MMC3 derivative
     *                   206 DxROM, Namco 118 / MIMIC-1
     *                   210 Namco 175 and 340
     *                   228 Action 52
     *                   232 Camerica/Codemasters Quattro
     *
     *  \return The mapper number
     */
    inline size_t getMapperNumber() const
    {
        return mMapperNumber;
    }

    /*
     *  \func getIsFourScreenMode
     *  \brief Does this use four screen instead of V/H mirroring?
     *
     *  \return True if the ROM uses four screen mode
     */
    inline bool getIsFourScreenMode() const
    {
        return mFourScreenMode;
    }

    /*
     *  \func getHasTrainer
     *  \brief Does the ROM have a trainer? This is not fully supported.
     *         If you have a trainer, it would be best to get a ROM without
     *         one.
     *
     *  \return True if the ROM has a trainer.
     */
    inline bool getHasTrainer() const
    {
        return mTrainer;
    }

    /*
     *  \func getHasBatteryBack
     *  \brief Does the ROM include battery backed RAM?
     *
     *  \return True if the ROM has battery backed RAM
     */
    inline bool getHasBatteryBack() const
    {
        return mBatteryBack;
    }

    /*
     *  \func getMirroring
     *  \brief Gets the mirroring mode of the ROM
     *
     *  \return The mirroring mode.
     */
    inline Mirroring getMirroring() const
    {
        return mMirroring;
    }

    /*
     *  \func getIsPlayChoice10
     *  \brief Returns if the cartridge supports PlayChoice-10. This is used
     *         to make game look better with 2C03 RGB PPU. It handles
     *         color emphasis differently than a standard NES PPU.
     *
     *  \return True if the ROM is PlayChoice-10
     */
    inline bool getIsPlayChoice10() const
    {
        return mPlayChoice10;
    }

    /*
     *  \func getIsVsUnisystem
     *  \brief Returns true if game is actually for the Nintendo VS System.
     *
     *  \return True if the ROM is Nintendo VS System.
     */
    inline bool getIsVsUnisystem() const
    {
        return mVsUnisystem;
    }

    /*
     *  \func getisNes2_0
     *  \brief Returns true if this game uses an NES 2.0 header.
     *
     *  \return True if the ROM uses a NES 2.0 header.
     */
    inline bool getIsNes2_0() const
    {
        return mIsNes2_0;
    }

    /*
     *  \func getNESIdentifier
     *  \brief Returns the NES file ID. This should always be "NES". If it
     *         is not set to "NES" then the file was not a NES ROM.
     *
     *  \return The NES identifier as a string.
     */
    inline std::string getNESIdentifier() const
    {
        return mNESIdentifier;
    }

    /*
     *  \func getHeaderSize
     *  \brief Return the number of bytes that should be in a header.
     *
     *  \return The number bytes in a header.
     */
    static size_t getHeaderSize()
    {
        return HEADER_SIZE;
    }

    /*
     *  \func createBinary
     *  \brief Creates the binary information required to make a NES Header.
     *         This can be used to create the NES Header in memory by passing
     *         the output into a Header constructor.
     *
     *  \param id The NES ID. This should always be "NES"
     *  \param progSize The number prog ROM banks
     *  \param chrRomSize The number of chr ROM banks
     *  \param mapper The mapper number
     *  \param fourScreenMode Is the ROM four screen?
     *  \param trainer Does the ROM have a trainer?
     *  \param batteryBack Does the ROM have battery backed RAM?
     *  \param mirroring The mirroring mode
     *  \param playChoice Is the ROM PlayChoice-10?
     *  \param vsUnisystem Is the ROM a Nintendo VS System ROM?
     *  \param isNes2_0 Is the ROM NES 2.0?
     *  \param extra The remaining bytes in the Header. You can pass in
     *         an empty vector and that would be valid.
     *         These bytes are not used, but can be maintained if you are
     *         trying to match an existing file.
     */
    static std::vector<uint8_t> createBinary(
            const std::string& id,
            size_t progSize,
            size_t chrRomSize,
            size_t mapper,
            bool fourScreenMode,
            bool trainer,
            bool batteryBack,
            Mirroring mirroring,
            bool playChoice,
            bool vsUnisystem,
            bool isNes2_0,
            const std::vector<uint8_t>& extra);

    /*
     *  \func Operator Equals
     *  \brief Checks if a Header is equal to another Header. This does
     *         check the extra unused bytes as well. Those may be different
     *         but the Header is functionally the same.
     *
     *  \param other The Header to check against.
     *  \return True if the Headers are equal.
     */
    bool operator==(const Header& other) const
    {
        return mNESIdentifier == other.mNESIdentifier &&
               mProgSize == other.mProgSize &&
               mChrRomSize == other.mChrRomSize &&
               mMapperNumber == other.mMapperNumber &&
               mFourScreenMode == other.mFourScreenMode &&
               mTrainer == other.mTrainer &&
               mBatteryBack == other.mBatteryBack &&
               mMirroring == other.mMirroring &&
               mPlayChoice10 == other.mPlayChoice10 &&
               mVsUnisystem == other.mVsUnisystem &&
               mIsNes2_0 == other.mIsNes2_0 &&
               mUnused == other.mUnused;
    }

private:
    std::vector<uint8_t> toBinary() const
    {
        return createBinary(mNESIdentifier,
                            mProgSize,
                            mChrRomSize,
                            mMapperNumber,
                            mFourScreenMode,
                            mTrainer,
                            mBatteryBack,
                            mMirroring,
                            mPlayChoice10,
                            mVsUnisystem,
                            mIsNes2_0,
                            mUnused);
    }

    NYRA_SERIALIZE()

    template<class Archive>
    void serialize(Archive& archive, const unsigned int version)
    {
        archive & mNESIdentifier;
        archive & mProgSize;
        archive & mChrRomSize;
        archive & mMapperNumber;
        archive & mFourScreenMode;
        archive & mTrainer;
        archive & mBatteryBack;
        archive & mMirroring;
        archive & mPlayChoice10;
        archive & mVsUnisystem;
        archive & mIsNes2_0;
        archive & mUnused;
    }

    friend std::ostream& operator<<(std::ostream& os, const Header& header);

    static const size_t HEADER_SIZE;

    std::string mNESIdentifier;
    size_t mProgSize;
    size_t mChrRomSize;
    size_t mMapperNumber;
    bool mFourScreenMode;
    bool mTrainer;
    bool mBatteryBack;
    Mirroring mMirroring;
    bool mPlayChoice10;
    bool mVsUnisystem;
    bool mIsNes2_0;
    std::vector<uint8_t> mUnused;
};
}
}
}

#endif
