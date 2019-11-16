package com.biotech.ble.showlog

import android.view.LayoutInflater
import android.view.ViewGroup
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView
import com.biotech.ble.R

/**
 * @author TuXin
 * @date 2019-11-16 13:21.
 *
 * Email : tuxin@pupupula.com
 */
class LogAdapter : RecyclerView.Adapter<LogAdapter.LogViewHolder>() {
    private val mData = mutableListOf<String>()

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): LogViewHolder {
        return LogViewHolder(parent)
    }

    override fun getItemCount(): Int {
        return mData.size
    }

    override fun onBindViewHolder(holder: LogViewHolder, position: Int) {
        holder.bind(mData[position])
    }

    fun addItem(text: String) {
        mData.add(text)
        notifyItemInserted(mData.size - 1)
    }

    class LogViewHolder(viewGroup: ViewGroup) : RecyclerView.ViewHolder(
        LayoutInflater.from(viewGroup.context).inflate(
            R.layout.log_item,
            viewGroup,
            false
        )
    ) {
        private val textView: TextView = itemView.findViewById<TextView>(R.id.textView)

        fun bind(text: String) {
            textView.text = text
        }
    }

}