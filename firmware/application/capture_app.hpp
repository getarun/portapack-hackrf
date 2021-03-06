/*
 * Copyright (C) 2016 Jared Boone, ShareBrained Technology, Inc.
 *
 * This file is part of PortaPack.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef __CAPTURE_APP_HPP__
#define __CAPTURE_APP_HPP__

#include "ui_widget.hpp"
#include "ui_navigation.hpp"
#include "ui_receiver.hpp"
#include "ui_record_view.hpp"
#include "ui_spectrum.hpp"

#include <string>
#include <memory>

namespace ui {

class CaptureAppView : public View {
public:
	CaptureAppView(NavigationView& nav);
	~CaptureAppView();

	void on_hide() override;

	void set_parent_rect(const Rect new_parent_rect) override;

	void focus() override;

	std::string title() const override { return "Capture"; };

private:
	static constexpr ui::Dim header_height = 2 * 16;

	static constexpr uint32_t sampling_rate = 4000000;
	static constexpr uint32_t baseband_bandwidth = 2500000;

	void on_target_frequency_changed(rf::Frequency f);

	rf::Frequency target_frequency() const;
	void set_target_frequency(const rf::Frequency new_value);

	rf::Frequency tuning_frequency() const;

	RSSI rssi {
		{ 24 * 8, 0, 6 * 8, 4 },
	};

	Channel channel {
		{ 24 * 8, 5, 6 * 8, 4 },
	};

	FrequencyField field_frequency {
		{ 0 * 8, 0 * 16 },
	};
	
	FrequencyStepView field_frequency_step {
		{ 10 * 8, 0 * 16 },
	};

	RFAmpField field_rf_amp {
		{ 16 * 8, 0 * 16 }
	};

	LNAGainField field_lna {
		{ 18 * 8, 0 * 16 }
	};

	VGAGainField field_vga {
		{ 21 * 8, 0 * 16 }
	};

	RecordView record_view {
		{ 0 * 8, 1 * 16, 30 * 8, 1 * 16 },
		u"BBD_????", RecordView::FileType::RawS16, 16384, 3
	};

	spectrum::WaterfallWidget waterfall;
};

} /* namespace ui */

#endif/*__CAPTURE_APP_HPP__*/
