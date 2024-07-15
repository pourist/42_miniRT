/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppour-ba <ppour-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:38:39 by ppour-ba          #+#    #+#             */
/*   Updated: 2024/07/12 11:45:37 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*find_error_5(int type)
{
	if (type == POINT_RANGE)
		return (POINT_RANGE_M);
	else if (type == HEIGHT_VALID)
		return (H_INVALID);
	else if (type == HEIGHT_RANGE)
		return (H_RANGE_M);
	else if (type == RADIUS)
		return (R_INVALID);
	else if (type == RADIUS_RANGE)
		return (R_RANGE_M);
	else if (type == OPEN_RANGE || type == OPEN)
		return (ERR_BOOL);
	else if (type == WIDTH_VALID)
		return (W_INVALID);
	else if (type == WIDTH_RANGE)
		return (W_RANGE_M);
	else if (type == DEPTH_VALID)
		return (DEPTH_INVALID);
	else if (type == DEPTH_RANGE)
		return (DEPTH_RANGE_M);
	else if (type == DIF_VALID)
		return (DIF_INVALID_M);
	else
		return (find_error_6(type));
}

char	*find_error_4(int type)
{
	if (type == DIF_RANGE)
		return (DIF_RANGE_M);
	else if (type == SPEC_VALID)
		return (SPEC_INVALID_M);
	else if (type == SPEC_RANGE)
		return (SPEC_RANGE_M);
	else if (type == SHINE_VALID)
		return (SHINE_INVALID_M);
	else if (type == SHINE_RANGE)
		return (SHINE_RANGE_M);
	else if (type == REF_VALID)
		return (REF_INVALID_M);
	else if (type == REF_RANGE)
		return (REF_RANGE_M);
	else if (type == TRANS_VALID)
		return (TRANS_INVALID_M);
	else if (type == TRANS_RANGE)
		return (TRANS_RANGE_M);
	else if (type == RIF_VALID)
		return (RIF_INVALID_M);
	else if (type == RIF_RANGE)
		return (RIF_RANGE_M);
	else
		return (find_error_5(type));
}

char	*find_error_3(int type)
{
	if (type == CENT_INVALID)
		return (CENT_INVALID_M);
	else if (type == CENT_RANGE)
		return (CENT_RANGE_M);
	else if (type == NORMAL_)
		return (NORMAL_M);
	else if (type == NORMAL_INVALID)
		return (NORMAL_INVALID_M);
	else if (type == NORMAL_RANGE)
		return (NORMAL_RANGE_M);
	else if (type == POINT)
		return (POINT_COUNT_M);
	else if (type == POINT_INVALID)
		return (POINT_INVALID_M);
	else if (type == UV_VEC)
		return (UV_LIGHT_VEC_M);
	else if (type == UV_STEPS)
		return (UV_LIGHT_STEPS_M);
	else if (type == SPOTLIGHT_CRADIAN)
		return (SPOTLIGHT_CRADIAN_M);
	else if (type == SPOTLIGHT_FRADIAN)
		return (SPOTLIGHT_FRADIAN_M);
	else if (type == SCALE)
		return (SCALE_COUNT_M);
	else if (type == SCALE_INVALID)
		return (SCALE_INVALID_M);
	else if (type == SCALE_RANGE)
		return (SCALE_RANGE_M);
	else
		return (find_error_4(type));
}

char	*find_error_2(int type)
{
	if (type == OR)
		return (OR_M);
	if (type == OR_INVALID)
		return (OR_INVALID_M);
	if (type == OR_RANGE)
		return (OR_RANGE_M);
	if (type == L_RATIO)
		return (L_RATIO_M);
	if (type == L_RATIO_RANGE)
		return (L_RATIO_RANGE_M);
	if (type == POS)
		return (POS_M);
	if (type == POS_INVALID)
		return (POS_INVALID_M);
	if (type == POS_RANGE)
		return (POS_RANGE_M);
	if (type == DIAM)
		return (D_INVALID);
	if (type == DIAM_RANGE)
		return (D_RANGE_M);
	if (type == CENT)
		return (CENT_M);
	return (find_error_3(type));
}

char	*find_error(int type)
{
	if (type == RATIO)
		return (RATIO_INVALID);
	else if (type == RATIO_OUT_RANGE)
		return (RATIO_RANGE);
	else if (type == RGB)
		return (RGB_LEN);
	else if (type == RGB_VALID)
		return (RGB_INVALID);
	else if (type == RGB_OUT_RANGE)
		return (RGB_RANGE);
	else if (type == FOV)
		return (FOV_M);
	else if (type == FOV_RANGE)
		return (FOV_RANGE_M);
	else if (type == POV)
		return (POV_M);
	else if (type == POV_INVALID)
		return (POV_INVALID_M);
	else if (type == POV_RANGE)
		return (POV_RANGE_M);
	else if (type == DOF)
		return (DOF_M);
	else
		return (find_error_2(type));
}
